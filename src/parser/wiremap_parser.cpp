#include "parser/wiremap_parser.hpp"
#include "parser/device_parser.hpp"
#include "parser/util.hpp"
#include "util.hpp"
#include "types.hpp"
#include "constant.hpp"
#include "wiremap.hpp"

namespace wiremap::parser{
    void WireMapParser::parse(const std::vector<std::string>& LINES){
        for(unsigned i = 0; i < LINES.size(); i++){
            if(indentCount(LINES[i]) == 0){
                std::vector<std::string> split_line = splitLine(LINES[i]);

                std::vector<std::string> scope = captureScope(LINES, i);
                i += scope.size() - 1; //skip scope in next search

                if(!DeviceNodes::exists(split_line[DEVICE_TYPE_POS])){
                    NYI //TODO error, device not found in project
                }
                printf("Found:%s\n", DeviceNodes::get(split_line[DEVICE_TYPE_POS]).toString().c_str());

                //TODO construct device and add it
                WireMap::add(split_line[DEVICE_NAME_POS], std::make_pair(std::string("NYI"), Constant<Integer>(0)));
            }
        }
        NYI
    }
}
