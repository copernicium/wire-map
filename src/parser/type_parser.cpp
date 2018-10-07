#include "parser/type_parser.hpp"

#include <string_view>

#include "parser/util.hpp"
#include "util.hpp"

namespace wiremap::parser{
    std::string asString(const Type::BaseType& IN){
        switch(IN){
        case Type::BaseType::LIST:
            return "\"List\"";
        case Type::BaseType::COLLECTION:
            return "\"Collection\"";
        case Type::BaseType::PRIMITIVE:
            return "\"Primitive\"";
        default:
            NYI
        }
    }

    std::string asString(const Type::PrimitiveType& IN){
        switch(IN){
        case Type::PrimitiveType::BIT:
            return "\"Bit\"";
        case Type::PrimitiveType::CHAR:
            return "\"Char\"";
        case Type::PrimitiveType::BYTE:
            return "\"Byte\"";
        case Type::PrimitiveType::WORD:
            return "\"Word\"";
        case Type::PrimitiveType::DWORD:
            return "\"DWord\"";
        case Type::PrimitiveType::QWORD:
            return "\"QWord\"";
        case Type::PrimitiveType::INTEGER:
            return "\"Integer\"";
        case Type::PrimitiveType::BOOL:
            return "\"Bool\"";
        case Type::PrimitiveType::REAL:
            return "\"Real\"";
        default:
            NYI
        }
    }

    Type::PrimitiveType parsePrimitiveType(const std::string& IN){
        if(IN == "Bit"){
            return Type::PrimitiveType::BIT;
        } else if(IN == "Char"){
            return Type::PrimitiveType::CHAR;
        } else if(IN == "Byte"){
            return Type::PrimitiveType::BYTE;
        } else if(IN == "Word"){
            return Type::PrimitiveType::WORD;
        } else if(IN == "DWord"){
            return Type::PrimitiveType::DWORD;
        } else if(IN == "QWord"){
            return Type::PrimitiveType::QWORD;
        } else if(IN == "Integer"){
            return Type::PrimitiveType::INTEGER;
        } else if(IN == "Bool"){
            return Type::PrimitiveType::BOOL;
        } else if(IN == "Real"){
            return Type::PrimitiveType::REAL;
        }
        printf("IN:%s\n",IN.c_str());
        NYI
    }

    Type Type::parseObject(const std::string& PRIMITIVE_TYPE){
        return Type(parsePrimitiveType(PRIMITIVE_TYPE));
    }

    Type Type::parseList(const std::vector<std::string>& IN){
        assert(isList(IN));

        return Type(UnderlyingListType{
            std::make_shared<Type>(
                Type::parse(subvector(IN, LIST_SIZE_POS + 1, IN.size()))
            ),
            std::stoi(IN[LIST_SIZE_POS])
		});
    }

    Type Type::parseCollection(const std::vector<std::string>& IN){
        assert(isCollection(IN));

        Type type;
        type.base_type = BaseType::COLLECTION;
        type.underlying_type = UnderlyingCollectionType();
        unsigned start = CONTAINER_SPECIFIER_POS + 1;
        for(unsigned i = start; i < IN.size(); i++){
            if(IN[i] == COLLECTION_SEPARATOR){
                std::get<UnderlyingCollectionType>(type.underlying_type).push_back(
                    std::make_shared<Type>(
                        Type::parse(subvector(IN, start, i))
                    )
                );
                start = i + 1;
            }
        }
        std::get<UnderlyingCollectionType>(type.underlying_type).push_back( //capture last type in collection
            std::make_shared<Type>(
                Type::parse(subvector(IN, start, IN.size()))
            )
        );
        return type;
    }

    Type::BaseType Type::getBaseType()const{
        return base_type; //TODO replace with type check on underlying_type?
    }

    Type::PrimitiveType Type::getObjectType()const{
        assert(base_type == BaseType::PRIMITIVE);
        return std::get<PrimitiveType>(underlying_type);
    }

    unsigned Type::getListSize()const{
        assert(base_type == BaseType::LIST);
        return std::get<UnderlyingListType>(underlying_type).second;
    }

    Type Type::getListType()const{
        assert(base_type == BaseType::LIST);
        assert(std::get<UnderlyingListType>(underlying_type).first != nullptr);
        return *(std::get<UnderlyingListType>(underlying_type).first);
    }

    std::vector<Type> Type::getCollectionTypes()const{
        assert(base_type == BaseType::COLLECTION);
        std::vector<Type> v;
        for(const std::shared_ptr<Type>& a: std::get<UnderlyingCollectionType>(underlying_type)){
            assert(a != nullptr);
            v.push_back(*a);
        }
        return v;
    }

    bool Type::isList(const std::vector<std::string>& IN){
        return IN.size() > LIST_SIZE_POS && IN[CONTAINER_KEYWORD_POS] == LIST_KEYWORD && IN[CONTAINER_SPECIFIER_POS] == CONTAINER_TYPE_SPECIFIER && isNumber(IN[LIST_SIZE_POS]);
    }

    bool Type::isCollection(const std::vector<std::string>& IN){
        return IN.size() > CONTAINER_SPECIFIER_POS && IN[CONTAINER_KEYWORD_POS] == COLLECTION_KEYWORD && IN[CONTAINER_SPECIFIER_POS] == CONTAINER_TYPE_SPECIFIER;
    }

    Type Type::parse(const std::vector<std::string>& IN){
        assert(!IN.empty());

        if(isCollection(IN)){
            return Type::parseCollection(IN);
        } else if(isList(IN)){
            return Type::parseList(IN);
        }
		if(TypeMap::exists(IN.front())){
			return TypeMap::get(IN.front());
		}
		return Type::parseObject(IN.front());
    }

    Type Type::parse(const std::string& in){
        return parse(splitLine(in));
    }

    std::string Type::toString()const{
        std::string a = "{";
        a += "\"base_type\":" + asString(getBaseType()) + ", ";
        switch(base_type){
        case BaseType::LIST:
            a += "\"underlying_type\":" + getListType().toString() + ", ";
            a += "\"list_size\":" + std::to_string(getListSize());
            break;
        case BaseType::COLLECTION:
            a += "\"underlying_type\":" + asString(getCollectionTypes(), &Type::toString);
            break;
        case BaseType::PRIMITIVE:
            a += "\"underlying_type\":" + asString(getObjectType());
            break;
        default:
            NYI
        }
        a += "}";
        return a;
    }

    Type::Type(){}

    Type::Type(const PrimitiveType& U): base_type(Type::BaseType::PRIMITIVE), underlying_type(U){}

	Type::Type(const UnderlyingListType& U): base_type(Type::BaseType::LIST), underlying_type(U){}

	Type::Type(const UnderlyingCollectionType& U): base_type(Type::BaseType::COLLECTION), underlying_type(U){}

    bool operator==(const Type& a, const Type& b){
        if(a.base_type != b.base_type){
            return false;
        }
        if(a.underlying_type.index() != b.underlying_type.index()){
            return false;
        }
        switch(a.base_type){
        case Type::BaseType::PRIMITIVE:
            return a.underlying_type == b.underlying_type;
        case Type::BaseType::LIST:
        {
            Type::UnderlyingListType a_under = std::get<Type::UnderlyingListType>(a.underlying_type);
            Type::UnderlyingListType b_under = std::get<Type::UnderlyingListType>(b.underlying_type);
            if(a_under.second != b_under.second){
                return false;
            }
            if(a_under.first != nullptr && b_under.first != nullptr){
                return *a_under.first == *b_under.first;
            }
            return a_under.first == b_under.first;
        }
        case Type::BaseType::COLLECTION:
        {
            Type::UnderlyingCollectionType a_under = std::get<Type::UnderlyingCollectionType>(a.underlying_type);
            Type::UnderlyingCollectionType b_under = std::get<Type::UnderlyingCollectionType>(b.underlying_type);
            if(a_under.size() != b_under.size()){
                return false;
            }
            for(unsigned i = 0; i < a_under.size(); i++){
                if(a_under[i] != nullptr && b_under[i] != nullptr &&
                   *(a_under[i]) != *(b_under[i])
                ){
                    return false;
                }
                if(a_under[i] != b_under[i]){
                    return false;
                }
            }
            return true;
        }
        default:
            NYI
        }
    }

    bool operator!=(const Type& a, const Type& b){
        return !(a == b);
    }
}
