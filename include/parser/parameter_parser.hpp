#pragma once

#include "parser/type_parser.hpp"

namespace wiremap::parser{
    struct ParameterNode{
	private:
        std::string name;

        Type type;

        std::optional<std::string> source_device;

        std::optional<std::string> source_result;

        static constexpr std::string_view KEYWORD = "Parameter";

		static constexpr unsigned MIN_DECLARATION_TERMS = 3;

	public:
		std::string getName()const;

		Type getType()const;

		std::optional<std::string> getSourceDevice()const;

		std::optional<std::string> getSourceResult()const;

		static bool identify(const std::vector<std::string>&);

        static ParameterNode parse(const std::vector<std::string>&);

        static ParameterNode parse(const std::string&);

        std::string toString()const;

        ParameterNode();

        ParameterNode(const std::string&, const Type&, const std::optional<std::string>&, const std::optional<std::string>&);
    };

    bool operator==(const ParameterNode&, const ParameterNode&);
}
