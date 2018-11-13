#pragma once

#include "parser/type_parser.hpp"

namespace wiremap::parser{
    struct ObjectNode{
        std::string name;
        TypeNode type;

		static ObjectNode parse(const Line&);
    };
}
