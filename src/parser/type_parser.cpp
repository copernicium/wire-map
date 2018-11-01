#include "parser/type_parser.hpp"

#include <string_view>

#include "parser/util.hpp"
#include "util.hpp"

namespace wiremap::parser{
    std::string asString(const TypeNode::BaseType& IN){
        switch(IN){
        case TypeNode::BaseType::LIST:
            return "\"List\"";
        case TypeNode::BaseType::COLLECTION:
            return "\"Collection\"";
        case TypeNode::BaseType::PRIMITIVE:
            return "\"Primitive\"";
        default:
            NYI
        }
    }

    std::string asString(const TypeNode::PrimitiveType& IN){
        switch(IN){
        case TypeNode::PrimitiveType::BIT:
            return "\"Bit\"";
        case TypeNode::PrimitiveType::CHAR:
            return "\"Char\"";
        case TypeNode::PrimitiveType::BYTE:
            return "\"Byte\"";
        case TypeNode::PrimitiveType::WORD:
            return "\"Word\"";
        case TypeNode::PrimitiveType::DWORD:
            return "\"DWord\"";
        case TypeNode::PrimitiveType::QWORD:
            return "\"QWord\"";
        case TypeNode::PrimitiveType::INTEGER:
            return "\"Integer\"";
        case TypeNode::PrimitiveType::BOOL:
            return "\"Bool\"";
        case TypeNode::PrimitiveType::REAL:
            return "\"Real\"";
        default:
            NYI
        }
    }

    TypeNode::PrimitiveType parsePrimitiveType(const std::string& IN){
        if(IN == "Bit"){
            return TypeNode::PrimitiveType::BIT;
        } else if(IN == "Char"){
            return TypeNode::PrimitiveType::CHAR;
        } else if(IN == "Byte"){
            return TypeNode::PrimitiveType::BYTE;
        } else if(IN == "Word"){
            return TypeNode::PrimitiveType::WORD;
        } else if(IN == "DWord"){
            return TypeNode::PrimitiveType::DWORD;
        } else if(IN == "QWord"){
            return TypeNode::PrimitiveType::QWORD;
        } else if(IN == "Integer"){
            return TypeNode::PrimitiveType::INTEGER;
        } else if(IN == "Bool"){
            return TypeNode::PrimitiveType::BOOL;
        } else if(IN == "Real"){
            return TypeNode::PrimitiveType::REAL;
        }
        printf("IN:%s\n",IN.c_str());
        NYI
    }

    TypeNode TypeNode::parseObject(const std::string& PRIMITIVE_TYPE){
        return TypeNode(parsePrimitiveType(PRIMITIVE_TYPE));
    }

    TypeNode TypeNode::parseList(const std::vector<std::string>& IN){
        assert(isList(IN));

        return TypeNode(UnderlyingListType{
            std::make_shared<TypeNode>(
                TypeNode::parse(subvector(IN, LIST_SIZE_POS + 1, IN.size()))
            ),
            std::stoi(IN[LIST_SIZE_POS])
		});
    }

    TypeNode TypeNode::parseCollection(const std::vector<std::string>& IN){
        assert(isCollection(IN));

        TypeNode type;
        type.base_type = BaseType::COLLECTION;
        type.underlying_type = UnderlyingCollectionType();
        unsigned start = CONTAINER_SPECIFIER_POS + 1;
        for(unsigned i = start; i < IN.size(); i++){
            if(IN[i] == COLLECTION_SEPARATOR){
                std::get<UnderlyingCollectionType>(type.underlying_type).push_back(
                    std::make_shared<TypeNode>(
                        TypeNode::parse(subvector(IN, start, i))
                    )
                );
                start = i + 1;
            }
        }
        std::get<UnderlyingCollectionType>(type.underlying_type).push_back( //capture last type in collection
            std::make_shared<TypeNode>(
                TypeNode::parse(subvector(IN, start, IN.size()))
            )
        );
        return type;
    }

    TypeNode::BaseType TypeNode::getBaseType()const{
        return base_type; //TODO replace with type check on underlying_type?
    }

    TypeNode::PrimitiveType TypeNode::getObjectType()const{
        assert(base_type == BaseType::PRIMITIVE);
        return std::get<PrimitiveType>(underlying_type);
    }

    unsigned TypeNode::getListSize()const{
        assert(base_type == BaseType::LIST);
        return std::get<UnderlyingListType>(underlying_type).second;
    }

    TypeNode TypeNode::getListType()const{
        assert(base_type == BaseType::LIST);
        assert(std::get<UnderlyingListType>(underlying_type).first != nullptr);
        return *(std::get<UnderlyingListType>(underlying_type).first);
    }

    std::vector<TypeNode> TypeNode::getCollectionTypes()const{
        assert(base_type == BaseType::COLLECTION);
        std::vector<TypeNode> v;
        for(const std::shared_ptr<TypeNode>& a: std::get<UnderlyingCollectionType>(underlying_type)){
            assert(a != nullptr);
            v.push_back(*a);
        }
        return v;
    }

    bool TypeNode::isList(const std::vector<std::string>& IN){
        return IN.size() > LIST_SIZE_POS && IN[CONTAINER_KEYWORD_POS] == LIST_KEYWORD && IN[CONTAINER_SPECIFIER_POS] == CONTAINER_TYPE_SPECIFIER && isNumber(IN[LIST_SIZE_POS]);
    }

    bool TypeNode::isCollection(const std::vector<std::string>& IN){
        return IN.size() > CONTAINER_SPECIFIER_POS && IN[CONTAINER_KEYWORD_POS] == COLLECTION_KEYWORD && IN[CONTAINER_SPECIFIER_POS] == CONTAINER_TYPE_SPECIFIER;
    }

    TypeNode TypeNode::parse(const std::vector<std::string>& IN){
        assert(!IN.empty());

        if(isCollection(IN)){
            return TypeNode::parseCollection(IN);
        } else if(isList(IN)){
            return TypeNode::parseList(IN);
        }
		if(TypeMap::exists(IN.front())){
			return TypeMap::get(IN.front());
		}
		return TypeNode::parseObject(IN.front());
    }

    TypeNode TypeNode::parse(const std::string& in){
        return parse(splitLine(in));
    }

    std::string TypeNode::toString()const{
        std::string a = "{";
        a += "\"base_type\":" + asString(getBaseType()) + ", ";
        switch(base_type){
        case BaseType::LIST:
            a += "\"underlying_type\":" + getListType().toString() + ", ";
            a += "\"list_size\":" + std::to_string(getListSize());
            break;
        case BaseType::COLLECTION:
            a += "\"underlying_type\":" + asString(getCollectionTypes(), &TypeNode::toString);
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

    TypeNode::TypeNode(){}

    TypeNode::TypeNode(const PrimitiveType& U): base_type(TypeNode::BaseType::PRIMITIVE), underlying_type(U){}

	TypeNode::TypeNode(const UnderlyingListType& U): base_type(TypeNode::BaseType::LIST), underlying_type(U){}

	TypeNode::TypeNode(const UnderlyingCollectionType& U): base_type(TypeNode::BaseType::COLLECTION), underlying_type(U){}

    bool operator==(const TypeNode& a, const TypeNode& b){
        if(a.base_type != b.base_type){
            return false;
        }
        if(a.underlying_type.index() != b.underlying_type.index()){
            return false;
        }
        switch(a.base_type){
        case TypeNode::BaseType::PRIMITIVE:
            return a.underlying_type == b.underlying_type;
        case TypeNode::BaseType::LIST:
        {
            TypeNode::UnderlyingListType a_under = std::get<TypeNode::UnderlyingListType>(a.underlying_type);
            TypeNode::UnderlyingListType b_under = std::get<TypeNode::UnderlyingListType>(b.underlying_type);
            if(a_under.second != b_under.second){
                return false;
            }
            if(a_under.first != nullptr && b_under.first != nullptr){
                return *a_under.first == *b_under.first;
            }
            return a_under.first == b_under.first;
        }
        case TypeNode::BaseType::COLLECTION:
        {
            TypeNode::UnderlyingCollectionType a_under = std::get<TypeNode::UnderlyingCollectionType>(a.underlying_type);
            TypeNode::UnderlyingCollectionType b_under = std::get<TypeNode::UnderlyingCollectionType>(b.underlying_type);
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

    bool operator!=(const TypeNode& a, const TypeNode& b){
        return !(a == b);
    }
}
