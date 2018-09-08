#pragma once

#include "parser/type_parser.hpp"

namespace wiremap::parser{
    struct ConstantNode{
        std::string name; //TODO hash?

        Type type;

        std::optional<std::string> value;

        static constexpr std::string_view KEYWORD = "Constant";

        static ConstantNode parse(const std::vector<std::string>&);
        static ConstantNode parse(const std::string&);

        std::string toString()const;
    };
}
