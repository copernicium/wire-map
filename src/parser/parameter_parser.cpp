#include "parser/parameter_parser.hpp"

#include "parser/util.hpp"
#include <cassert>

namespace wiremap::parser{
	std::string ParameterNode::getName()const{
		return name;
	}

	Type ParameterNode::getType()const{
		return type;
	}

	std::optional<std::string> ParameterNode::getSourceDevice()const{
		return source_device;
	}

	std::optional<std::string> ParameterNode::getSourceResult()const{
		return source_result;
	}

	bool ParameterNode::identify(const std::vector<std::string>& LINE){
		return LINE.size() >= MIN_DECLARATION_TERMS && LINE.front() == KEYWORD;
	}

	ParameterNode ParameterNode::parse(const std::vector<std::string>& LINE){
        assert(identify(LINE));

        ParameterNode parameter_node;
        parameter_node.name = LINE[LINE.size() - 1];
        parameter_node.type = Type::parse(subvector(LINE, 1, LINE.size() - 1));

        return parameter_node;
    }

    ParameterNode ParameterNode::parse(const std::string& LINE){
        return parse(splitLine(LINE));
    }

    std::string ParameterNode::toString()const{
        std::string a = "{";
        a += "\"name\":\"" + name + "\", ";
        a += "\"type\":" + type.toString() + ", ";
        a += "\"source_device\":" + (source_device ? source_device.value() : "null") + ", ";
        a += "\"source_result\":" + (source_result ? source_result.value() : "null");
        a += "}";
        return a;
    }

    ParameterNode::ParameterNode(){}

    ParameterNode::ParameterNode(const std::string& NAME, const Type& TYPE, const std::optional<std::string>& SD, const std::optional<std::string>& SR): name(NAME), type(TYPE), source_device(SD), source_result(SR){}

    bool operator==(const ParameterNode& a, const ParameterNode& b){
        return a.getName() == b.getName() && a.getType() == b.getType() && a.getSourceDevice() == b.getSourceDevice() && a.getSourceResult() == b.getSourceResult();
    }
}
