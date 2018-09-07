#pragma once

#include "parser/type_parser.hpp"

namespace wiremap::parser{
    struct ResultNode{
        std::string name;
        Type type;
        //TODO generating function

        static constexpr std::string_view KEYWORD = "Result";
    };

    std::optional<ResultNode> parseResult(const std::string&);
}
