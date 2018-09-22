#include "parser/result_parser.hpp"

#include "parser/util.hpp"
#include <cassert>

namespace wiremap::parser{
    ResultNode ResultNode::parse(const std::vector<std::string>& split_line){
        return {"", {}}; //TODO
    }

    ResultNode ResultNode::parse(const std::string& LINE){
        return parse(splitLine(LINE));
    }

    std::string ResultNode::toString()const{
        std::string a = "{";
        a += "\"name\":\"" + name + "\", ";
        a += "\"type\":" + type.toString() + ", ";
        a += "}";
        return a;
    }

    ResultNode::ResultNode(){}
    ResultNode::ResultNode(const std::string& NAME, const Type& TYPE): name(NAME), type(TYPE){}

    bool operator==(const ResultNode& a, const ResultNode& b){
        return a.name == b.name && a.type == b.type;
    }
}
