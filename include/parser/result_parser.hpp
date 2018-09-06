#pragma once

#include "parser/type_parser.hpp"

namespace wiremap::parser{
    struct ResultNode{
        std::string name;
        Type type;
        //TODO generating function
    };

    std::optional<ResultNode> parseResult(const std::string&);
}
