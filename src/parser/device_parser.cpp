#include "parser/device_parser.hpp"

#include "parser/util.hpp"
#include "util.hpp"

#include <string_view>

namespace wiremap::parser{
    bool DeviceNode::identifierIsDevice(const std::vector<std::string>& LINE){
        return LINE.size() == REQUIRED_LINE_SIZE && LINE[KEYWORD_POS] == KEYWORD;
    }

    std::string parseDeviceName(const std::vector<std::string>& LINE){
        if(DeviceNode::identifierIsDevice(LINE)){
            return {LINE[1]};
        }
        assert(0);
    }

    DeviceNode DeviceNode::parse(const std::vector<std::string>& IN){
        assert(!IN.empty());

        constexpr unsigned DEVICE_START_LINE = 0;

        DeviceNode device_node;
        device_node.name = parseDeviceName(splitLine(IN[DEVICE_START_LINE]));

        for(unsigned i = DEVICE_START_LINE + 1; i < IN.size(); i++){
            unsigned indent_count = indentCount(IN[i]);
            if(indent_count != 1 && !IN[i].empty()){
                if(indent_count == 0){ //end of device definition
                    break;
                }
                continue;
            }
            std::vector<std::string> split_line = splitLine(IN[i]);
            if(!split_line.empty()){
                if(split_line.front() == ParameterNode::KEYWORD){
                    device_node.parameters.push_back(ParameterNode::parse(split_line));
                } else if(split_line.front() == ConstantNode::KEYWORD){
                    device_node.constants.push_back(ConstantNode::parse(split_line));
                } else if(split_line.front() == ResultNode::KEYWORD){
                } else {
                    NYI
                }
            }
        }
        return device_node;
    }

    std::string DeviceNode::toString()const{
        std::string a = "{";
        a += "\"name\":\"" + name + "\", ";
        a += "\"parameters\":" + asString(parameters, &ParameterNode::toString) + ", ";
        a += "\"constants\":" + asString(constants, &ConstantNode::toString) + ", ";
        a += "\"results\":" + asString(results, &ResultNode::toString);
        a += "}";
        return a;
    }

    DeviceNode::DeviceNode(){}
    DeviceNode::DeviceNode(const std::string& NAME, const std::vector<ParameterNode>& P, const std::vector<ConstantNode>& C, const std::vector<ResultNode>& R): name(NAME), parameters(P), constants(C), results(R){}

    bool operator==(const DeviceNode& a, const DeviceNode& b){
        return a.name == b.name && a.parameters == b.parameters && a.constants == b.constants && a.results == b.results;
    }
}
