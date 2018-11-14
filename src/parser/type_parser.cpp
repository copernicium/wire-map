#include "parser/type_parser.hpp"

#include "parser/util.hpp"
#include "util.hpp"

namespace wiremap::parser{
    std::shared_ptr<google::dense_hash_map<wiremap::detail::KeyType,TypeNode,wiremap::detail::Hasher,wiremap::detail::KeyCompare>> TypeMap::types = nullptr;

    std::string asString(const Type& IN){
        switch(IN){
        case Type::UNKNOWN:
            return "\"UNKNOWN\"";
        case Type::BIT:
            return "\"BIT\"";
        case Type::CHAR:
            return "\"CHAR\"";
        case Type::BYTE:
            return "\"BYTE\"";
        case Type::WORD:
            return "\"WORD\"";
        case Type::DWORD:
            return "\"DWORD\"";
        case Type::QWORD:
            return "\"QWORD\"";
        case Type::INTEGER:
            return "\"INTEGER\"";
        case Type::BOOL:
            return "\"BOOL\"";
        case Type::REAL:
            return "\"REAL\"";
        case Type::CONTAINER:
            return "\"CONTAINER\"";
        default:
            NYI
        }
    }

    Type parsePrimitiveType(const std::string& IN){
        if(IN == "Bit"){
            return Type::BIT;
        } else if(IN == "Char"){
            return Type::CHAR;
        } else if(IN == "Byte"){
            return Type::BYTE;
        } else if(IN == "Word"){
            return Type::WORD;
        } else if(IN == "DWord"){
            return Type::DWORD;
        } else if(IN == "QWord"){
            return Type::QWORD;
        } else if(IN == "Integer"){
            return Type::INTEGER;
        } else if(IN == "Bool"){
            return Type::BOOL;
        } else if(IN == "Real"){
            return Type::REAL;
        }
        printf("IN:%s\n",IN.data());
        NYI
    }

    TypeNode TypeNode::parsePrimitive(const std::string& PRIMITIVE_TYPE){
        return TypeNode(parsePrimitiveType(PRIMITIVE_TYPE));
    }

    TypeNode TypeNode::parseList(const Line& IN){
        assert(isList(IN));

        return TypeNode(
                TypeNode::parse(IN.segment(LIST_SIZE_POS + 1, IN.size())),
				std::stoi(static_cast<std::string>(IN[LIST_SIZE_POS]))
		);
    }

    TypeNode TypeNode::parseCollection(const Line& IN){
        assert(isCollection(IN));

		std::vector<TypeNode> types;

        unsigned start = CONTAINER_SPECIFIER_POS + 1;
        for(unsigned i = start; i < IN.size(); i++){
            if(IN[i] == SYMBOLS[COMMA]){
                types.push_back(
					TypeNode::parse(IN.segment(start, i))
                );
                start = i + 1;
            }
        }
        types.push_back( //capture last type in collection
			TypeNode::parse(IN.segment(start, IN.size()))
		);
        return TypeNode(types);
    }

    bool TypeNode::isList(const Line& IN){
        return IN.size() > LIST_SIZE_POS && IN[CONTAINER_KEYWORD_POS] == LIST_KEYWORD && IN[CONTAINER_SPECIFIER_POS] == CONTAINER_TYPE_SPECIFIER && isNumber(IN[LIST_SIZE_POS]);
    }

    bool TypeNode::isCollection(const Line& IN){
        return IN.size() > CONTAINER_SPECIFIER_POS && IN[CONTAINER_KEYWORD_POS] == COLLECTION_KEYWORD && IN[CONTAINER_SPECIFIER_POS] == CONTAINER_TYPE_SPECIFIER;
    }

    TypeNode TypeNode::parse(const Line& IN){
        assert(!IN.empty());

        if(isCollection(IN)){
            return TypeNode::parseCollection(IN);
        } else if(isList(IN)){
            return TypeNode::parseList(IN);
        }
		if(TypeMap::exists(IN.front())){
			return TypeMap::get(IN.front());
		}
		return TypeNode::parsePrimitive(IN.front());
    }

	Object TypeNode::getType()const{
		assert(inner.has_value());
		return inner.value();
	}

    std::string TypeNode::toString()const{
		assert(inner.has_value());

        std::string a = "{";
		a += "\"base_type\":";
		if(inner.value().getType() != Type::CONTAINER){
			a += "\"PRIMITIVE\", ";
            a += "\"underlying_type\":" + asString(inner.value().getType());
		} else {
			a += "\"CONTAINER\", ";
            a += "\"underlying_type\": [";
			for(auto i = inner.value().begin(); i != inner.value().end(); ++i){
				if(i != inner.value().begin()){
					a += ",";
				}
				a += TypeNode(**i).toString();
			}
			a += "], ";
            a += "\"size\":" + std::to_string(inner.value().size());
		}
        a += "}";
        return a;
    }

    TypeNode::TypeNode(){}

    TypeNode::TypeNode(const Object& T): inner(T){}

    TypeNode::TypeNode(const Type& T): inner(Object::primitive(T)){}

	TypeNode::TypeNode(const TypeNode& T, const unsigned& SIZE){
		assert(T.inner.has_value());
		inner = Object::list(T.inner.value(), SIZE);
	}

	TypeNode::TypeNode(const std::vector<TypeNode>& T){
		std::vector<Object> inners;
		for(const TypeNode& A: T){
			assert(A.inner.has_value());
			inners.push_back(A.inner.value());
		}
		inner = Object::collection(inners);
	}

    bool operator==(const TypeNode& A, const TypeNode& B){
		return A.inner == B.inner;
	}

    bool operator!=(const TypeNode& a, const TypeNode& b){
        return !(a == b);
    }
}
