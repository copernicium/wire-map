#pragma once

#include <optional>
#include <string>

namespace wiremap::parser{
    struct ObjectNode{
        std::string name;
        std::string type;
    };

    std::optional<ObjectNode> parseObject(const std::string&);
}
