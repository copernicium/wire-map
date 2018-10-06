#include "parser/device_parser.hpp"

#include "parser/util.hpp"
#include "util.hpp"

#include <string_view>

namespace wiremap::parser{
	std::string DeviceNode::getName()const{
		return name;
	}

	std::vector<ParameterNode> DeviceNode::getParameters()const{
		return parameters;
	}

	std::vector<ConstantNode> DeviceNode::getConstants()const{
		return constants;
	}
	std::vector<ResultNode> DeviceNode::getResults()const{
		return results;
	}

    bool DeviceNode::identify(const std::vector<std::string>& LINE){
        return LINE.size() == REQUIRED_LINE_SIZE && LINE[KEYWORD_POS] == KEYWORD;
    }

    std::string parseDeviceName(const std::vector<std::string>& LINE){
        if(DeviceNode::identify(LINE)){
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
            if(!split_line.empty()){ //TODO all names must be unique within device
                if(ParameterNode::identify(split_line)){
                    device_node.parameters.push_back(ParameterNode::parse(split_line));
                } else if(ConstantNode::identify(split_line)){
                    device_node.constants.push_back(ConstantNode::parse(split_line));
                } else if(ResultNode::identify(split_line)){
                    device_node.results.push_back(ResultNode::parse(split_line));//TODO not split line but scope
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
        return a.getName() == b.getName() && a.getParameters() == b.getParameters() && a.getConstants() == b.getConstants() && a.getResults() == b.getResults();
    }
}
