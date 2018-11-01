#pragma once

#include "parser/type_parser.hpp"

namespace wiremap::parser{
    struct ConstantNode{
	private:
		std::string name;

        TypeNode type;

        std::optional<std::string> value;

        static constexpr std::string_view KEYWORD = "Constant";

	public:
		std::string getName()const;

		TypeNode getType()const;

		std::optional<std::string> getValue()const;

		static bool identify(const std::vector<std::string>&);

        static ConstantNode parse(const std::vector<std::string>&);

        static ConstantNode parse(const std::string&);

        ConstantNode();

        ConstantNode(const std::string&, const TypeNode&, const std::optional<std::string>&);

        std::string toString()const;
    };

    bool operator==(const ConstantNode&, const ConstantNode&);
}
