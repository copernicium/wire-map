#pragma once

#include "map_util.hpp"

#include <array>
#include <string_view>
#include <vector>

namespace wiremap::parser{
	class Line{
		unsigned indentation;

		std::vector<std::string> tokens;

		Line();
		Line(unsigned, const std::vector<std::string>&);

	public:
		const std::vector<std::string>& getTokens()const;

		const std::string& operator[](const unsigned&)const;

		const std::string& at(const unsigned&)const;

		std::size_t size()const;

		bool empty()const;

		const std::string& front()const;

		const std::string& back()const;

		std::vector<std::string>::const_iterator begin()const noexcept;

		std::vector<std::string>::const_iterator end()const noexcept;

		unsigned getIndentation()const;

		Line segment(const std::size_t&, const std::size_t&)const;

		static Line tokenize(const std::string&);
	};

	using Lines = std::vector<Line>;

	enum Symbol{
		COMMENT,
		COMMA,
		DOT,
		OPEN_PAREN,
		CLOSE_PARN,
		ASSIGN,
		GREATER,
		LESS,
		GREATER_EQUAL,
		LESS_EQUAL,
		PLUS,
		MINUS,
		MULT,
		DIV,
		PLUS_EQUAL,
		MINUS_EQUAL,
		MULT_EQUAL,
		DIV_EQUAL,
		PARAMETER_SOURCE,
		SYMBOL_SIZE
	};

	constexpr std::array<std::string_view, Symbol::SYMBOL_SIZE> SYMBOLS = { // TODO add more
		"#",
		",",
		".",
		"(",
		")",
		"=",
		">",
		"<",
		">=",
		"<=",
		"+",
		"-",
		"*",
		"/",
		"+=",
		"-=",
		"*=",
		"/=",
		"<-"
	};
}
