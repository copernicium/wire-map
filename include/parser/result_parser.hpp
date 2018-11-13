#pragma once

#include "parser/type_parser.hpp"

namespace wiremap::parser{
    struct ResultNode{
	private:
		std::string name;

        TypeNode type;

        //TODO generating function

        static constexpr std::string_view KEYWORD = "Result";

		static constexpr unsigned MIN_DECLARATION_TERMS = 3;

	public:
		std::string getName()const;

		TypeNode getType()const;

		static bool identify(const Line&);

        static ResultNode parse(const Line&);

        ResultNode();

		ResultNode(const std::string&, const TypeNode&);

        std::string toString()const;
    };

    bool operator==(const ResultNode&, const ResultNode&);
}
