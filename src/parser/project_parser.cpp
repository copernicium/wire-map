#include "parser/project_parser.hpp"
#include "parser/device_parser.hpp"
#include "parser/wiremap_parser.hpp"
#include "parser/util.hpp"
#include "util.hpp"
#include <fstream>

namespace wiremap::parser{
    std::vector<std::string> readFile(const std::filesystem::path& FILE){ //consider splitting every line here
        std::ifstream file_stream(FILE, std::ifstream::in);
        if(!file_stream.is_open() || file_stream.peek() == std::ifstream::traits_type::eof()){
            return {};
        }
        std::string line;
        std::vector<std::string> lines;

		while(std::getline(file_stream, line)){
            if(!line.empty()){
                lines.push_back(line);
            }
        }
        return lines;
    }

    void Project::parseFile(const std::filesystem::path& FILE){
        if(FILE.extension() != FILE_EXTENSION){
            return;
        }

        const std::vector<std::string> LINES = readFile(FILE);

		if(FILE.stem() == PROJECT_MAIN_FILE_NAME){
            WireMapParser::parse(LINES);
        } else {
			for(unsigned i = 0; i < LINES.size(); i++){
				if(indentCount(LINES[i]) == 0){
					std::vector<std::string> line = splitLine(LINES[i]);

					if(DeviceNode::identify(line)){
						std::vector<std::string> scope = captureScope(LINES, i);
						i += scope.size() - 1; //skip scope in next search

						DeviceNodes::parse(scope);
					} else if(TypeMap::identify(line)){
						TypeMap::parse(line);
					}
				}
			}
        }
    }

    void Project::parse(const std::filesystem::path& PROJECT_PATH){
        std::optional<std::filesystem::path> main_file;
        for(const std::filesystem::directory_entry& a: std::filesystem::directory_iterator(PROJECT_PATH)){
            if(a.is_regular_file()){
                if(a.path().stem() == PROJECT_MAIN_FILE_NAME){
                    main_file = a;
                } else {
                    parseFile(a);
                }
            }
        }
        if(main_file.has_value()){ // Parse main file lastly to set up device instances
            parseFile(main_file.value());
        }
    }
}
