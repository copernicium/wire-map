#pragma once

#include "parser/type_parser.hpp"

namespace wiremap::parser{
    struct ConstantNode{
        std::string name;
        Type type;

        static constexpr std::string_view KEYWORD = "Constant";
    };

    std::optional<ConstantNode> parseConstant(const std::string&);
}
