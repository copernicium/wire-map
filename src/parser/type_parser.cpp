#include "parser/type_parser.hpp"

#include <string_view>

#include "parser/alias_parser.hpp"
#include "parser/util.hpp"

namespace wiremap::parser{
    std::optional<Type> parseType(const std::vector<std::string>& in){
        if(in.empty()){
            return {};
        }

        constexpr std::string_view COLLECTION_KEYWORD = "Collection";
        constexpr std::string_view LIST_KEYWORD = "List";

        Type type;

        if(std::find(in.begin(),in.end(),COLLECTION_KEYWORD) != in.end()){
            type.base_type = Type::BaseType::COLLECTION;
            //TODO add underlying types
        } else if(std::find(in.begin(),in.end(),LIST_KEYWORD) != in.end()){
            type.base_type = Type::BaseType::LIST;
            //TODO add underlying types
        } else {
            type.base_type = Type::BaseType::OBJECT;
            //TODO add underlying types
        }

        return {type};
    }

    std::optional<Type> parseType(const std::string& in){
        return parseType(splitLine(in));
    }
}
