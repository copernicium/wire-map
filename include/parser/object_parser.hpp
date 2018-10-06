#pragma once

#include "parser/type_parser.hpp"

namespace wiremap::parser{
    struct ObjectNode{
        std::string name;
        Type type;

		static ObjectNode parse(const std::string&);
    };
}
