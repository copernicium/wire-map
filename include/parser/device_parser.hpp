#pragma once

#include <optional>
#include <vector>

#include "parser/object_parser.hpp"
#include "parser/result_parser.hpp"

namespace wiremap::parser{
    struct DeviceNode{
        std::string name;

        std::vector<ObjectNode> parameters;
        std::vector<ObjectNode> constants;
        std::vector<ResultNode> results;

        static constexpr std::string_view KEYWORD = "Device";
    };

    std::optional<DeviceNode> parseDevice(std::vector<std::string>&);
}
