#include "parser/device_parser.hpp"

#include "parser/util.hpp"
#include "util.hpp"

namespace wiremap::parser{
    std::shared_ptr<google::dense_hash_map<wiremap::detail::KeyType,DeviceNode,wiremap::detail::Hasher,wiremap::detail::KeyCompare>> DeviceNodes::device_nodes = nullptr;

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

	int DeviceNode::getParameter(const std::string& NAME)const{
		for(unsigned i = 0; i < parameters.size(); i++){
			if(parameters[i].getName() == NAME){
				return i;
			}
		}
		return -1;
	}

	bool DeviceNode::isConstant(const std::string& NAME)const{
		for(const ConstantNode& A: constants){
			if(A.getName() == NAME){
				return true;
			}
		}
		return false;
	}

	bool DeviceNode::isResult(const std::string& NAME)const{
		for(const ResultNode& A: results){
			if(A.getName() == NAME){
				return true;
			}
		}
		return false;
	}

    bool DeviceNode::identify(const Line& LINE){
        return LINE.size() == REQUIRED_LINE_SIZE && LINE[KEYWORD_POS] == KEYWORD;
    }

    DeviceNode DeviceNode::parse(const Lines& SCOPE){
        assert(!SCOPE.empty() && identify(SCOPE.front()));

        DeviceNode device_node;
        device_node.name = SCOPE.front()[1];

        for(unsigned i = 1; i < SCOPE.size(); i++){ // skip first line (name)
            unsigned indent_count = SCOPE[i].getIndentation();
            if(indent_count != 1 && !SCOPE[i].empty()){
                if(indent_count == 0){ //end of device definition
                    break;
                }
                continue;
            }

            const Line& line = SCOPE[i];

			if(!line.empty()){ //TODO all names must be unique within device
                if(ParameterNode::identify(line)){
                    device_node.parameters.push_back(ParameterNode::parse(line));
                } else if(ConstantNode::identify(line)){
                    device_node.constants.push_back(ConstantNode::parse(line));
                } else if(ResultNode::identify(line)){
                    device_node.results.push_back(ResultNode::parse(line));//TODO not split line but scope
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
