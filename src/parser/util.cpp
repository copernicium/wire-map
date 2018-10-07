#include "parser/util.hpp"
#include <cassert>

namespace wiremap::parser{
    std::vector<std::string> splitLine(const std::string& LINE){
		if(LINE.empty()){
			return {};
		}

		constexpr char DELIMITER = ' ';
		constexpr char SEPARATOR = ',';

        std::vector<std::string> split;

		std::string::const_iterator start = LINE.begin();
		while(*start == DELIMITER && start != LINE.end()){
			start++;
		}

		for(std::string::const_iterator i = start; i != LINE.end(); ++i){
            if(*i == DELIMITER || *i == SEPARATOR){ //TODO split at ( and ) ?
				split.emplace_back(start, i);
				while(*i == DELIMITER && i != (LINE.end() - 1)){
					++i;
				}
				start = i;
            } else if(*i == detail::COMMENT_START){
                break;
            }
        }
		if(*start != DELIMITER){ // capture last part of line if it's not a delimiter
			split.emplace_back(start, LINE.end());
		}
        return split;
    }

    unsigned indentCount(const std::string& LINE){
        if(LINE.size() < detail::INDENT.size()){
            return false;
        }
        std::size_t spaces = LINE.find_first_not_of(" ");
        if(spaces == std::string::npos){
            return 0;
        }
        assert(spaces % detail::INDENT.size() == 0);
        return spaces / detail::INDENT.size();
    }

    bool isNumber(const std::string& IN){
        for(const char& c: IN){
            if(!std::isdigit(c)){
                return false;
            }
        }
        return true;
    }

    std::vector<std::string> captureScope(const std::vector<std::string>& LINES, unsigned scope_start){
        if(LINES.empty()){
            return LINES;
        }
        assert(scope_start < LINES.size());
        unsigned scope_indent_count = indentCount(LINES[scope_start]);
        unsigned scope_end = 0;
        for(scope_end = scope_start + 1; scope_end < LINES.size(); scope_end++){//start search on next line
            if(indentCount(LINES[scope_end]) <= scope_indent_count){
                break;
            }
        }
        return subvector(LINES, scope_start, scope_end);
    }
}
