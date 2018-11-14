#include "parser/constant_parser.hpp"

#include "parser/util.hpp"
#include <cassert>

namespace wiremap::parser{
	std::string ConstantNode::getName()const{
		return name;
	}

	TypeNode ConstantNode::getType()const{
		return type;
	}

	ConstantNode ConstantNode::parse(const Line& LINE){
        assert(LINE.size() >= 3);

        ConstantNode constant_node;
        constant_node.name = LINE[LINE.size() - 1];
        constant_node.type = TypeNode::parse(LINE.segment(1, LINE.size() - 1));

        return constant_node;
    }

    std::string ConstantNode::toString()const{
        std::string a = "{";
        a += "\"name\":\"" + name + "\", ";
        a += "\"type\":" + type.toString();
        a += "}";
        return a;
    }

	bool ConstantNode::identify(const Line& LINE){
		return LINE.size() >= 3 && LINE.front() == ConstantNode::KEYWORD;
	}

    ConstantNode::ConstantNode(){}

    ConstantNode::ConstantNode(const std::string& NAME, const TypeNode& TYPE): name(NAME), type(TYPE){}

    bool operator==(const ConstantNode& a, const ConstantNode& b){
        return a.getName() == b.getName() && a.getType() == b.getType();
    }
}
