#include "parser/result_parser.hpp"

#include "parser/util.hpp"
#include <cassert>

namespace wiremap::parser{
    ResultNode ResultNode::parse(const std::vector<std::string>& split_line){
        assert(split_line.size() >= 3);

        ResultNode result_node;
        result_node.name = split_line[split_line.size() - 1];
        result_node.type = Type::parse(subvector(split_line, 1, split_line.size() - 1));
        //TODO generating function
        return result_node;
    }

    ResultNode ResultNode::parse(const std::string& LINE){
        return parse(splitLine(LINE));
    }

    std::string ResultNode::toString()const{
        std::string a = "{";
        a += "\"name\":\"" + name + "\", ";
        a += "\"type\":" + type.toString();
        //TODO generating function
        a += "}";
        return a;
    }

    ResultNode::ResultNode(){}
    ResultNode::ResultNode(const std::string& NAME, const Type& TYPE): name(NAME), type(TYPE){}

    bool operator==(const ResultNode& a, const ResultNode& b){
        return a.name == b.name && a.type == b.type;
    }
}
