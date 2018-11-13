#pragma once //TODO determine if there is confusion between util.hpp and parser/util.hpp

#include "map_util.hpp"
#include "parser/tokenizer.hpp"

#include <functional>

namespace wiremap::parser{
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

    Lines captureScope(const Lines&, unsigned scope_start = 0);

    template<typename T>
    std::vector<T> subvector(const std::vector<T>& SOURCE, const std::size_t& START, const std::size_t& END){
        return std::vector<T>{SOURCE.begin() + START, SOURCE.begin() + END};
    }
}
