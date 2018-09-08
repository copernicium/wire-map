#pragma once

#include <functional>
#include <string>
#include <string_view>
#include <vector>

namespace wiremap::parser{
    namespace detail{
        constexpr std::string_view INDENT = "    ";
        constexpr char COMMENT_START = '#';
    }

    std::vector<std::string> splitLine(const std::string&);

    unsigned indentCount(const std::string&);

    bool isNumber(const std::string&);

    template<typename T>
    std::string asString(const T& iterable, std::function<std::string(typename T::value_type)> to_s){
        std::string a = "[";
        for(auto i = iterable.begin(); i != iterable.end(); ++i){
            if(i != iterable.begin()){
                a += ",";
            }
            a += to_s(*i);
        }
        a += "]";
        return a;
    }
}
