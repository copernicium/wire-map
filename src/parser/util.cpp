#include "parser/util.hpp"
#include <cassert>

namespace wiremap::parser{
    std::vector<std::string> splitLine(const std::string& LINE){
        std::vector<std::string> v;
        std::string a;
        for(unsigned i = 0; i < LINE.size(); i++){
            const char& c = LINE[i];
            if(c == ' ' || c == ','){ //TODO split at ( and ) ?
                if(!a.empty()){
                    v.push_back(a);
                    a = "";
                }
                if(c == ','){
                    v.push_back(",");
                }
            } else if(c == detail::COMMENT_START){
                break;
            } else {
                a += c;
            }
        }
        if(a != ""){
            v.push_back(a);
        }
        return v;
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
