#include "parser/parser.hpp"
#include "parser/alias_parser.hpp"
#include "parser/device_parser.hpp"
#include "parser/util.hpp"
#include "util.hpp"
#include <fstream>

namespace wiremap::parser{
    std::vector<std::string> readFile(const std::string& FILE_NAME){
        std::ifstream file_stream(FILE_NAME, std::ifstream::in);
        if(!file_stream.is_open() || file_stream.peek() == std::ifstream::traits_type::eof()){
            return {};
        }
        std::string line;
        std::vector<std::string> v;
        while(std::getline(file_stream, line)){
            if(!line.empty()){
                v.push_back(line);
            }
        }
        return v;
    }

    void parseFile(const std::vector<std::string>& LINES){
        for(unsigned i = 0; i < LINES.size(); i++){
            if(indentCount(LINES[i]) == 0){
                std::vector<std::string> split_line = splitLine(LINES[i]);

                std::vector<std::string> scope = captureScope(LINES, i);
                i += scope.size() - 1; //skip scope in next search

                if(split_line.size() > DeviceNode::KEYWORD_POS && split_line[DeviceNode::KEYWORD_POS] == DeviceNode::KEYWORD){
                    DeviceNode a = DeviceNode::parse(scope);
                    if(DeviceNodes::exists(a.name)){
                        NYI //TODO error, redefinition
                    }
                    DeviceNodes::add(a.name,a);
                } else if(split_line.size() > AliasMap::KEYWORD_POS && split_line[AliasMap::KEYWORD_POS] == AliasMap::KEYWORD){
                    if(AliasMap::exists(split_line.front())){
                        NYI //TODO error, redefinition
                    }
                    AliasMap::add(split_line.front(), Type::parse(std::vector<std::string>{split_line.begin() + AliasMap::KEYWORD_POS + 1, split_line.end()}));
                }
            }
        }
    }

    void parseFile(const std::string& FILE_NAME){
        parseFile(readFile(FILE_NAME));
    }
}
