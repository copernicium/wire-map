#pragma once

#include "parser/type_parser.hpp"

namespace wiremap::parser{
    struct ParameterNode{
        std::string name;

        Type type;

        std::optional<std::string> source_device;

        std::optional<std::string> source_result;

        static constexpr std::string_view KEYWORD = "Parameter";

        static ParameterNode parse(const std::vector<std::string>&);
        static ParameterNode parse(const std::string&);

        std::string toString()const;
    };
}
