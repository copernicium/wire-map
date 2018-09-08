#include "parser/util.hpp"
#include <cassert>

namespace wiremap::parser{
    std::vector<std::string> splitLine(const std::string& LINE){
        std::vector<std::string> v;
        std::string a;
        for(unsigned i = 0; i < LINE.size(); i++){
            const char& c = LINE[i];
            if(c == ' ' || (c == ',' && (i + 1) < LINE.size() && LINE[i + 1] == ' ')){ //TODO split at ( and ) ?
                if(!a.empty()){
                    v.push_back(a);
                    a = "";
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
}
