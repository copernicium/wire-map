#pragma once

#include <optional>
#include <vector>

#include "parser/object_parser.hpp"

namespace wiremap::parser{
    struct DeviceNode{
        std::string name;

        std::vector<ObjectNode> parameters;
        std::vector<ObjectNode> constants;
        std::vector<int> results; //TODO
    };

    std::optional<DeviceNode> parseDevice(std::vector<std::string>&);
}
