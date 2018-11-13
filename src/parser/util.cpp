#include "parser/util.hpp"
#include <cassert>

namespace wiremap::parser{
    bool isNumber(const std::string& IN){
        for(const char& c: IN){
            if(!std::isdigit(c)){
                return false;
            }
        }
        return true;
    }

    Lines captureScope(const Lines& LINES, unsigned scope_start){
        if(LINES.empty()){
            return LINES;
        }
        assert(scope_start < LINES.size());
        unsigned scope_indent_count = LINES[scope_start].getIndentation();
        unsigned scope_end = 0;
        for(scope_end = scope_start + 1; scope_end < LINES.size(); scope_end++){//start search on next line
            if(LINES[scope_end].getIndentation() <= scope_indent_count){
                break;
            }
        }
        return subvector(LINES, scope_start, scope_end);
    }
}
