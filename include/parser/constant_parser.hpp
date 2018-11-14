#pragma once

#include "parser/type_parser.hpp"

namespace wiremap::parser{
    struct ConstantNode{
	private:
		std::string name;

        TypeNode type;

        static constexpr std::string_view KEYWORD = "Constant";

	public:
		std::string getName()const;

		TypeNode getType()const;

		std::optional<std::string> getValue()const;

		static bool identify(const Line&);

        static ConstantNode parse(const Line&);

        ConstantNode();

        ConstantNode(const std::string&, const TypeNode&);

        std::string toString()const;
    };

    bool operator==(const ConstantNode&, const ConstantNode&);
}
