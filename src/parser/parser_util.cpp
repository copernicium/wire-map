#include "parser/parser_util.hpp"

#include "parser/parser_constants.hpp"

namespace wiremap::parser{
    std::vector<std::string> splitLine(const std::string& LINE){
        std::vector<std::string> v;
        std::string a;
        for(char c: LINE){
            if(c == ' '){
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
        return LINE.substr(0, detail::INDENT.size()) == detail::INDENT;
    }
}
