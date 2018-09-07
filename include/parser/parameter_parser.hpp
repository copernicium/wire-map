#pragma once

#include "parser/type_parser.hpp"

namespace wiremap::parser{
    struct ParameterNode{
        std::string name;

        Type type;

        std::optional<std::string> source_device;

        std::optional<std::string> source_result;

        static constexpr std::string_view KEYWORD = "Parameter";
    };

    std::optional<ParameterNode> parseParameter(const std::vector<std::string>&);
    std::optional<ParameterNode> parseParameter(const std::string&);
}
