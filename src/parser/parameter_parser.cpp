#include "parser/parameter_parser.hpp"

#include "parser/util.hpp"
#include <cassert>

namespace wiremap::parser{
	std::string ParameterNode::getName()const{
		return name;
	}

	TypeNode ParameterNode::getType()const{
		return type;
	}

	bool ParameterNode::identify(const Line& LINE){
		return LINE.size() >= MIN_DECLARATION_TERMS && LINE.front() == KEYWORD;
	}

	ParameterNode ParameterNode::parse(const Line& LINE){
        assert(identify(LINE));

        ParameterNode parameter_node;
        parameter_node.name = LINE[LINE.size() - 1];
        parameter_node.type = TypeNode::parse(LINE.segment(1, LINE.size() - 1));

        return parameter_node;
    }

	std::string ParameterNode::toString()const{
		std::string a = "{";
        a += "\"name\":\"" + name + "\", ";
        a += "\"type\":" + type.toString();
        a += "}";
        return a;
    }

    ParameterNode::ParameterNode(){}

    ParameterNode::ParameterNode(const std::string& NAME, const TypeNode& TYPE): name(NAME), type(TYPE){}

    bool operator==(const ParameterNode& a, const ParameterNode& b){
        return a.getName() == b.getName() && a.getType() == b.getType();
    }
}
