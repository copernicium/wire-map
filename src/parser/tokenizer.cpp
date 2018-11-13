#include "parser/tokenizer.hpp"

#include "parser/util.hpp"

#include <algorithm>
#include <cassert>

#include <iostream>

namespace wiremap::parser{
	Line::Line():indentation(0), tokens(){}

	Line::Line(unsigned I, const std::vector<std::string>& T): indentation(I), tokens(T){}

	const std::vector<std::string>& Line::getTokens()const{
		return tokens;
	}

	const std::string& Line::operator[](const unsigned& I)const{
		return tokens[I];
	}

	const std::string& Line::at(const unsigned& I)const{
		return tokens.at(I);
	}

	unsigned Line::getIndentation()const{
		return indentation;
	}

	std::size_t Line::size()const{
		return tokens.size();
	}

	bool Line::empty()const{
		return tokens.empty();
	}

	const std::string& Line::front()const{
		return tokens.front();
	}

	const std::string& Line::back()const{
		return tokens.back();
	}

	std::vector<std::string>::const_iterator Line::begin()const noexcept{
		return tokens.begin();
	}

	std::vector<std::string>::const_iterator Line::end()const noexcept{
		return tokens.end();
	}

	Line Line::segment(const std::size_t& START, const std::size_t& END)const{
		return {indentation, subvector(tokens, START, END)};
	}

	std::string nextSymbol(const std::string& LINE, std::size_t& start){
		assert(start < LINE.size());

		constexpr std::string_view IDENTIFIER_SEPARATOR = " ";

		std::string out;

		std::size_t first_symbol = LINE.size();

		for(const std::string_view& SYMBOL: SYMBOLS){
			std::size_t pos = LINE.find(SYMBOL, start);
			if(pos != std::string::npos && (pos < first_symbol || SYMBOL.size() > out.size())){ // Find first, largest matching symbol
				first_symbol = pos;
				out = SYMBOL;
			}
		}

		std::size_t first_separator = LINE.find(IDENTIFIER_SEPARATOR, start);

		if(first_separator != std::string::npos && first_separator < first_symbol){ // If a space is found before a token, collect the characters until the space
			out = LINE.substr(start, first_separator - start);
			start = first_separator + 1;
			return out;
		}

		if(!out.empty()){
			if(first_symbol != start){ // If a symbol is found that isn't the first token, collect until symbol
				out = LINE.substr(start, first_symbol - start);
				start = first_symbol;
			} else {
				start += out.size(); // Collect symbol
			}
			return out;
		}

		out = LINE.substr(start); // Otherwise, collect until end of line
		start = LINE.size();
		return out;
	}


	Line Line::tokenize(const std::string& LINE){
		constexpr std::string_view INDENT_SPACES = "    ";
		constexpr std::string_view INDENT_TAB = "\t";

		Line line;

		std::size_t start = 0;
		std::size_t indentation_stop = LINE.find_first_not_of(" \t");

		while(start < indentation_stop && indentation_stop != std::string::npos){
			std::size_t spaces = LINE.find(INDENT_SPACES, start);
			std::size_t tabs = LINE.find(INDENT_TAB, start);
			if(spaces != std::string::npos || tabs != std::string::npos){ // If an indent is found, increment
				line.indentation++;
				start = std::min( // Start search after first occurring indent
					(spaces == std::string::npos) ? indentation_stop : spaces + INDENT_SPACES.size(),
					(tabs == std::string::npos) ? indentation_stop : tabs + INDENT_TAB.size()
				);
			} else {
				break;
			}
		}
		while(start < LINE.size()){
			std::string token = nextSymbol(LINE, start);
			if(!token.empty()){
				line.tokens.push_back(token);
			}
		}

        return line;
    }
}
