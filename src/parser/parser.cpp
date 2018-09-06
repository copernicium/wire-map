#include "parser/parser.hpp"

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
            v.push_back(line);
        }
        return v;
    }
}
