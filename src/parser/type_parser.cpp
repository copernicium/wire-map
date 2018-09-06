#include "parser/type_parser.hpp"

#include <string_view>

#include "parser/alias_parser.hpp"

namespace wiremap::parser{

    std::optional<Type> parseType(const std::string& in){
        if(in.empty()){
            return {};
        }
        Type type;

        //TODO

        return {type};
    }
}
