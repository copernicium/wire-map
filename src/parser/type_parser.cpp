#include "parser/type_parser.hpp"

#include <string_view>

#include "parser/alias_parser.hpp"
#include "parser/util.hpp"
#include "util.hpp"

namespace wiremap::parser{
    std::string asString(const Type::BaseType& IN){
        switch(IN){
        case Type::BaseType::LIST:
            return "List";
        case Type::BaseType::COLLECTION:
            return "Collection";
        case Type::BaseType::OBJECT:
            return "Object";
        default:
            NYI
        }
    }

    std::string asString(const Type::UnderlyingType& IN){
        switch(IN){
        case Type::UnderlyingType::BIT:
            return "Bit";
        case Type::UnderlyingType::CHAR:
            return "Char";
        case Type::UnderlyingType::BYTE:
            return "Byte";
        case Type::UnderlyingType::WORD:
            return "Word";
        case Type::UnderlyingType::DWORD:
            return "DWord";
        case Type::UnderlyingType::QWORD:
            return "QWord";
        case Type::UnderlyingType::INTEGER:
            return "Integer";
        case Type::UnderlyingType::BOOL:
            return "Bool";
        case Type::UnderlyingType::REAL:
            return "Real";
        default:
            NYI
        }
    }

    Type::UnderlyingType parseUnderlyingType(const std::string& IN){
        if(IN == "Bit"){
            return Type::UnderlyingType::BIT;
        } else if(IN == "Char"){
            return Type::UnderlyingType::CHAR;
        } else if(IN == "Byte"){
            return Type::UnderlyingType::BYTE;
        } else if(IN == "Word"){
            return Type::UnderlyingType::WORD;
        } else if(IN == "DWord"){
            return Type::UnderlyingType::DWORD;
        } else if(IN == "QWord"){
            return Type::UnderlyingType::QWORD;
        } else if(IN == "Integer"){
            return Type::UnderlyingType::INTEGER;
        } else if(IN == "Bool"){
            return Type::UnderlyingType::BOOL;
        } else if(IN == "Real"){
            return Type::UnderlyingType::REAL;
        }
        NYI
    }

    Type Type::parseObject(const std::string& UNDERLYING_TYPE){
        Type type;
        type.base_type = BaseType::OBJECT;
        type.underlying_types = {parseUnderlyingType(UNDERLYING_TYPE)};
        return type;
    }

    Type Type::parseList(const std::vector<std::string>& IN){
        Type type;
        type.base_type = BaseType::LIST;
        for(const auto& a: IN){
            if(a != LIST_KEYWORD && a != CONTAINER_TYPE_SPECIFIER){
                if(isNumber(a)){
                    type.list_size = std::stoi(a);
                    continue;
                }
                type.underlying_types.push_back(parseUnderlyingType(a));
            }
        }
        assert(type.underlying_types.size() == 1);
        return type;
    }

    Type Type::parseCollection(const std::vector<std::string>& IN){
        Type type;
        type.base_type = BaseType::COLLECTION;
        for(const auto& a: IN){
            if(a != COLLECTION_KEYWORD && a != CONTAINER_TYPE_SPECIFIER){
                if(isNumber(a)){
                    type.list_size = std::stoi(a);
                    continue;
                }
                type.underlying_types.push_back(parseUnderlyingType(a));
            }
        }
        return type;
    }

    Type::BaseType Type::getBaseType()const{
        return base_type;
    }

    Type::UnderlyingType Type::getUnderlyingType()const{
        assert(base_type != BaseType::COLLECTION && !underlying_types.empty());
        return underlying_types.front();
    }

    std::vector<Type::UnderlyingType> Type::getUnderlyingTypes()const{
        assert(base_type == BaseType::COLLECTION);
        return underlying_types;
    }

    unsigned Type::getListSize()const{
        assert(base_type == BaseType::LIST);
        return list_size;
    }

    Type Type::parse(const std::vector<std::string>& in){
        assert(!in.empty());

        Type type;

        if(in.front() == COLLECTION_KEYWORD){
            type = Type::parseCollection(in);
        } else if(in.front() == LIST_KEYWORD){
            type = Type::parseList(in);
        } else {
            type = Type::parseObject(in.front());
        }

        return type;
    }

    Type Type::parse(const std::string& in){
        return parse(splitLine(in));
    }

    std::string Type::toString()const{
        std::string a = "{";
        a += "base_type:" + asString(getBaseType()) + ", ";
        if(base_type == BaseType::LIST){
            a += "list_size:" + std::to_string(getListSize()) + ", ";
        }
        if(base_type != BaseType::COLLECTION){
            a += "underlying_type:" + asString(getUnderlyingType());
        } else {
            a += "underlying_types:" + asString(getUnderlyingTypes(), static_cast<std::string(*)(const Type::UnderlyingType&)>(asString));
        }
        a += "}";
        return a;
    }
}
