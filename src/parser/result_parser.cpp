#include "parser/result_parser.hpp"

#include "parser/util.hpp"
#include <cassert>

namespace wiremap::parser{
    ResultNode ResultNode::parse(const std::vector<std::string>& split_line){
        return {};
    }

    ResultNode ResultNode::parse(const std::string& LINE){
        return parse(splitLine(LINE));
    }

    std::string ResultNode::toString()const{
        std::string a = "{";
        a += "}";
        return a;
    }
}
