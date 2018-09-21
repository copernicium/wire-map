#pragma once

#include "parser/device_parser.hpp"

namespace wiremap::parser{
    std::vector<std::string> readFile(const std::string&);

    void parseFile(const std::vector<std::string>&);

    void parseFile(const std::string&);
}
