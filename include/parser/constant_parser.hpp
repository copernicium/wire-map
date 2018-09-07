#pragma once

#include "parser/type_parser.hpp"

namespace wiremap::parser{
    struct ConstantNode{
        std::string name; //TODO hash?

        Type type;

        std::optional<std::string> value;

        static constexpr std::string_view KEYWORD = "Constant";
    };

    std::optional<ConstantNode> parseConstant(const std::string&);
}
