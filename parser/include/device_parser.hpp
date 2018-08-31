#pragma once

#include <optional>

#include "object_parser.hpp"
#include "parser_types.hpp"

namespace wiremap::parser{
    struct DeviceNode{
        std::string name;

        std::vector<ObjectNode> parameters;
        std::vector<ObjectNode> constants;
        std::vector<ObjectNode> results;
    };

    std::optional<DeviceNode> parseDevice(std::vector<std::string>&);
}
