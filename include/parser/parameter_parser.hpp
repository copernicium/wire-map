#pragma once

#include "parser/type_parser.hpp"
#include "parser/wiremap_parser.hpp"

namespace wiremap::parser{
    struct ParameterNode{
	private:
        std::string name;

        TypeNode type;

        static constexpr std::string_view KEYWORD = "Parameter";

		static constexpr unsigned MIN_DECLARATION_TERMS = 3;

	public:
		std::string getName()const;

		TypeNode getType()const;

		std::optional<std::string> getSourceDevice()const;

		std::optional<std::string> getSourceResult()const;

		static bool identify(const Line&);

        static ParameterNode parse(const Line&);

        std::string toString()const;

        ParameterNode();

        ParameterNode(const std::string&, const TypeNode&);

		friend WireMapParser;
    };

    bool operator==(const ParameterNode&, const ParameterNode&);
}
