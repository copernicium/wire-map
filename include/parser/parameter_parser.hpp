#pragma once

#include "parser/type_parser.hpp"

namespace wiremap::parser{
    struct ParameterNode{
        std::string name;
        Type type;

        static constexpr std::string_view KEYWORD = "Parameter";
    };

    std::optional<ParameterNode> parseParameter(const std::string&);
}
