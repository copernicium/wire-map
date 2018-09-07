#include "parser/device_parser.hpp"

#include "parser/util.hpp"

#include <iostream>
#include <string_view>

namespace wiremap::parser{

    std::optional<std::string> parseDeviceName(const std::vector<std::string>& LINE){
        constexpr unsigned DEVICE_FLAG_POS = 0;

        if(LINE.size() == 2 && LINE[DEVICE_FLAG_POS] == DeviceNode::KEYWORD){
            return {LINE[1]};
        }
        return {};
    }

    std::optional<DeviceNode> parseDevice(std::vector<std::string>& in){
        if(in.empty()){
            return {};
        }

        constexpr unsigned DEVICE_START_LINE = 0;
        unsigned end = 0;

        std::vector<std::string> name_split_line = splitLine(in[DEVICE_START_LINE]);
        std::optional<std::string> name = parseDeviceName(name_split_line);

        if(!name){
            return {};
        }

        DeviceNode device_node;
        device_node.name = name.value();

        for(unsigned i = DEVICE_START_LINE + 1; i < in.size(); i++){
            if(indentCount(in[i]) == 0 && !in[i].empty()){ //end of device definition
                break;
            }
            std::cout<<in[i]<<"\n";
            std::vector<std::string> split_line = splitLine(in[i]);
            if(!split_line.empty()){
                if(split_line[0] == ParameterNode::KEYWORD){
                    std::optional<ParameterNode> p = parseParameter(split_line);
                    if(p){
                        std::cout<<p.value().name<<"\n";
                        std::cout<<(p.value().type.base_type == Type::BaseType::OBJECT)<<"\n";
                    }
                } else if(split_line[0] == ConstantNode::KEYWORD){
                } else if(split_line[0] == ResultNode::KEYWORD){
                } else {
                    return {};
                }
                // std::cout<<split_line[0]<<"\n";
            }
            end++;
        }
        return {device_node};
    }
}
