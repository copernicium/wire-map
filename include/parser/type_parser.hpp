#pragma once

#include <algorithm>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

#include "map_util.hpp"
#include "parser/type_parser.hpp"
#include "parser/util.hpp"

namespace wiremap::parser{
    struct TypeNode{
        enum class BaseType{
            PRIMITIVE,
            LIST,
            COLLECTION
        };

        enum class PrimitiveType{
            BIT,
            CHAR,
            BYTE,
            WORD,
            DWORD,
            QWORD,
            INTEGER,
            BOOL,
            REAL
        };

        using UnderlyingListType = std::pair<std::shared_ptr<TypeNode>, std::size_t>;

        using UnderlyingCollectionType = std::vector<std::shared_ptr<TypeNode>>;

        using UnderlyingType = std::variant<PrimitiveType, UnderlyingListType, UnderlyingCollectionType>;

    private:
        static constexpr unsigned CONTAINER_KEYWORD_POS = 0;
        static constexpr unsigned CONTAINER_SPECIFIER_POS = 1;
        static constexpr unsigned LIST_SIZE_POS = 2;
        static constexpr std::string_view COLLECTION_KEYWORD = "Collection";
        static constexpr std::string_view LIST_KEYWORD = "List";
        static constexpr std::string_view CONTAINER_TYPE_SPECIFIER = "of";

        static bool isList(const Line&);

        static bool isCollection(const Line&);

        BaseType base_type;

        UnderlyingType underlying_type;

        static TypeNode parseObject(const std::string&); // TODO rename to parsePrimitive
        static TypeNode parseList(const Line&);
        static TypeNode parseCollection(const Line&);
    public:

        BaseType getBaseType()const;

        PrimitiveType getObjectType()const;

        unsigned getListSize()const;

        TypeNode getListType()const;

        std::vector<TypeNode> getCollectionTypes()const;

        static TypeNode parse(const Line&);

        TypeNode();
        TypeNode(const PrimitiveType&);
        TypeNode(const UnderlyingListType&);
        TypeNode(const UnderlyingCollectionType&);

        std::string toString()const;

        friend bool operator==(const TypeNode&, const TypeNode&);

		friend struct TypeMap;
    };

    bool operator==(const TypeNode&, const TypeNode&);
    bool operator!=(const TypeNode&, const TypeNode&);

    std::string asString(const TypeNode::BaseType&);

    struct TypeMap{
        static constexpr std::string_view KEYWORD = "as";
        static constexpr unsigned KEYWORD_POS = 1;
        static constexpr unsigned MINIMUM_LINE_SIZE = 3;

    private:
        static std::shared_ptr<google::dense_hash_map<wiremap::detail::KeyType,TypeNode,wiremap::detail::Hasher,wiremap::detail::KeyCompare>> types;

    public:
        static bool identify(const Line& LINE){
            return LINE.size() >= MINIMUM_LINE_SIZE && LINE[KEYWORD_POS] == KEYWORD;
        }

        static void reset(){
            types = std::make_shared<google::dense_hash_map<wiremap::detail::KeyType,TypeNode,wiremap::detail::Hasher,wiremap::detail::KeyCompare>>();
            types->set_empty_key(0);
            const std::array<std::string_view, 9> PRIMITIVES = {
                "Bit",
                "Char",
                "Byte",
                "Word",
                "DWord",
                "QWord",
                "Integer",
                "Bool",
                "Real"
            };
            for(const auto& a: PRIMITIVES){
                add(std::string(a),TypeNode::parseObject(std::string(a)));
            }
        }

        static void add(const wiremap::detail::KeyType& KEY, const TypeNode& VALUE)noexcept{
            if(types == nullptr){
                reset();
            }
            assert(!exists(KEY));
            (*types)[KEY] = VALUE;
        }

        static void add(const std::string& KEY, const TypeNode& VALUE)noexcept{
            add(hasher(KEY),VALUE);
        }

        static TypeNode& get(const wiremap::detail::KeyType& KEY)noexcept{
            assert(types != nullptr && types->find(KEY) != types->end());
            return (*types)[KEY];
        }

        static TypeNode& get(const std::string& KEY)noexcept{
            return get(hasher(KEY));
        }

        static bool exists(const wiremap::detail::KeyType& KEY)noexcept{
            if(types == nullptr){
                return false;
            }
            return types->find(KEY) != types->end();
        }

        static bool exists(const std::string& KEY)noexcept{
            return exists(hasher(KEY));
        }

        static void parse(const Line& LINE){
            if(LINE.empty() || !identify(LINE)){
                return;
            }
            if(exists(LINE.front())){
                exit(EXIT_FAILURE); //TODO error, redefinition
            }
            add(LINE.front(), TypeNode::parse(LINE.segment(KEYWORD_POS + 1, LINE.size())));
        }

        TypeMap() = delete;
    };
}
