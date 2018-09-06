#pragma once

#include <optional>
#include <string>

#include "parser/type_parser.hpp"

namespace wiremap::parser{
    struct ObjectNode{
        std::string name;
        Type type;
    };

    std::optional<ObjectNode> parseObject(const std::string&);
}
