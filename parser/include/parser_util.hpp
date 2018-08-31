#pragma once

#include "parser_types.hpp"

#include <vector>

namespace wiremap::parser{
    std::vector<std::string> splitLine(const std::string&);

    unsigned indentCount(const std::string&);
}
