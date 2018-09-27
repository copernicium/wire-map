#pragma once //TODO determine if there is confusion between util.hpp and parser/util.hpp

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

    std::vector<std::string> captureScope(const std::vector<std::string>&, unsigned scope_start = 0);

    template<typename T>
    std::vector<T> subvector(const std::vector<T>& SOURCE, const unsigned& START, const unsigned& END){
        return std::vector<T>{SOURCE.begin() + START, SOURCE.begin() + END};
    }
}
