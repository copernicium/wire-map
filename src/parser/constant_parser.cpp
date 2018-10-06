#include "parser/constant_parser.hpp"

#include "parser/util.hpp"
#include <cassert>

namespace wiremap::parser{
	std::string ConstantNode::getName()const{
		return name;
	}

	Type ConstantNode::getType()const{
		return type;
	}

	std::optional<std::string> ConstantNode::getValue()const{
		return value;
	}

	ConstantNode ConstantNode::parse(const std::vector<std::string>& split_line){
        assert(split_line.size() >= 3);

        ConstantNode constant_node;
        constant_node.name = split_line[split_line.size() - 1];
        constant_node.type = Type::parse(subvector(split_line, 1, split_line.size() - 1));

        return constant_node;
    }

    ConstantNode ConstantNode::parse(const std::string& LINE){
        return parse(splitLine(LINE));
    }

    std::string ConstantNode::toString()const{
        std::string a = "{";
        a += "\"name\":\"" + name + "\", ";
        a += "\"type\":" + type.toString() + ", ";
        a += "\"value\":" + (value ? value.value() : "null");
        a += "}";
        return a;
    }

	bool ConstantNode::identify(const std::vector<std::string>& LINE){
		return LINE.size() >= 3 && LINE.front() == ConstantNode::KEYWORD;
	}

    ConstantNode::ConstantNode(){}

    ConstantNode::ConstantNode(const std::string& NAME, const Type& TYPE, const std::optional<std::string>& V): name(NAME), type(TYPE), value(V){}

    bool operator==(const ConstantNode& a, const ConstantNode& b){
        return a.getName() == b.getName() && a.getType() == b.getType() && a.getValue() == b.getValue();
    }
}
