#pragma once

#include "parser/type_parser.hpp"

namespace wiremap::parser{
    struct ResultNode{
        std::string name;
        Type type;
        //TODO generating function

        static constexpr std::string_view KEYWORD = "Result";

        ResultNode parse(const std::vector<std::string>&);
        ResultNode parse(const std::string&);

        ResultNode();
        ResultNode(const std::string&, const Type&);

        std::string toString()const;
    };

    bool operator==(const ResultNode&, const ResultNode&);
}
