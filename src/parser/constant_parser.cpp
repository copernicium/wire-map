#include "parser/constant_parser.hpp"

#include "parser/util.hpp"
#include <cassert>

namespace wiremap::parser{
    ConstantNode ConstantNode::parse(const std::vector<std::string>& split_line){
        assert(split_line.size() >= 3);

        ConstantNode constant_node;
        constant_node.name = split_line[split_line.size() - 1];
        constant_node.type = Type::parse(std::vector<std::string>{split_line.begin() + 1, split_line.end() - 1});

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
}
