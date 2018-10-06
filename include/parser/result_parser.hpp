#pragma once

#include "parser/type_parser.hpp"

namespace wiremap::parser{
    struct ResultNode{
	private:
		std::string name;

        Type type;

        //TODO generating function

        static constexpr std::string_view KEYWORD = "Result";

	public:
		std::string getName()const;

		Type getType()const;

		static bool identify(const std::vector<std::string>&);

        static ResultNode parse(const std::vector<std::string>&);

		static ResultNode parse(const std::string&);

        ResultNode();

		ResultNode(const std::string&, const Type&);

        std::string toString()const;
    };

    bool operator==(const ResultNode&, const ResultNode&);
}
