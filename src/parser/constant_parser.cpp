#include "parser/constant_parser.hpp"

#include "parser/util.hpp"
#include <cassert>

namespace wiremap::parser{
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

    ConstantNode::ConstantNode(){}
    ConstantNode::ConstantNode(const std::string& NAME, const Type& TYPE, const std::optional<std::string>& V): name(NAME), type(TYPE), value(V){}

    bool operator==(const ConstantNode& a, const ConstantNode& b){
        return a.name == b.name && a.type == b.type && a.value == b.value;
    }
}
