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
    struct Type{
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

        using UnderlyingListType = std::pair<std::shared_ptr<Type>, std::size_t>;

        using UnderlyingCollectionType = std::vector<std::shared_ptr<Type>>;

        using UnderlyingType = std::variant<PrimitiveType, UnderlyingListType, UnderlyingCollectionType>;

    private:
        static constexpr unsigned CONTAINER_KEYWORD_POS = 0;
        static constexpr unsigned CONTAINER_SPECIFIER_POS = 1;
        static constexpr unsigned LIST_SIZE_POS = 2;
        static constexpr std::string_view COLLECTION_KEYWORD = "Collection";
        static constexpr std::string_view COLLECTION_SEPARATOR = ",";
        static constexpr std::string_view LIST_KEYWORD = "List";
        static constexpr std::string_view CONTAINER_TYPE_SPECIFIER = "of";

        static bool isList(const std::vector<std::string>&);

        static bool isCollection(const std::vector<std::string>&);

        BaseType base_type;

        UnderlyingType underlying_type;

        static Type parseObject(const std::string&);
        static Type parseList(const std::vector<std::string>&);
        static Type parseCollection(const std::vector<std::string>&);
    public:

        BaseType getBaseType()const;

        PrimitiveType getObjectType()const;

        unsigned getListSize()const;

        Type getListType()const;

        std::vector<Type> getCollectionTypes()const;

        static Type parse(const std::vector<std::string>&);
        static Type parse(const std::string&);

        Type();
        Type(const PrimitiveType&);
        Type(const UnderlyingListType&);
        Type(const UnderlyingCollectionType&);

        std::string toString()const;

        friend bool operator==(const Type&, const Type&);
    };

    bool operator==(const Type&, const Type&);
    bool operator!=(const Type&, const Type&);

    std::string asString(const Type::BaseType&);

    struct TypeMap{
        static constexpr std::string_view KEYWORD = "as";
        static constexpr unsigned KEYWORD_POS = 1;
        static constexpr unsigned MINIMUM_LINE_SIZE = 3;

    private:
        static std::shared_ptr<google::dense_hash_map<wiremap::detail::KeyType,Type,wiremap::detail::Hasher,wiremap::detail::KeyCompare>> types;

    public:
        static bool identify(const std::vector<std::string>& LINE){
            return LINE.size() >= MINIMUM_LINE_SIZE && LINE[KEYWORD_POS] == KEYWORD;
        }

        static void reset(){
            types = std::make_shared<google::dense_hash_map<wiremap::detail::KeyType,Type,wiremap::detail::Hasher,wiremap::detail::KeyCompare>>();
            types->set_empty_key(0);
            const std::array<std::string, 9> PRIMITIVES = {
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
                add(a,Type::parse(a));
            }
        }

        static void add(const wiremap::detail::KeyType& KEY, const Type& VALUE)noexcept{
            if(types == nullptr){
                reset();
            }
            assert(!exists(KEY));
            (*types)[KEY] = VALUE;
        }

        static void add(const std::string& KEY, const Type& VALUE)noexcept{
            add(hashstr(KEY),VALUE);
        }

        static Type& get(const wiremap::detail::KeyType& KEY)noexcept{
            assert(types != nullptr && types->find(KEY) != types->end());
            return (*types)[KEY];
        }

        static Type& get(const std::string& KEY)noexcept{
            return get(hashstr(KEY));
        }

        static bool exists(const wiremap::detail::KeyType& KEY)noexcept{
            if(types == nullptr){
                return false;
            }
            return types->find(KEY) != types->end();
        }

        static bool exists(const std::string& KEY)noexcept{
            return exists(hashstr(KEY));
        }

        static void parse(const std::vector<std::string>& LINE){
            if(LINE.empty() || !identify(LINE)){
                return;
            }
            if(exists(LINE.front())){
                exit(EXIT_FAILURE); //TODO error, redefinition
            }
            add(LINE.front(), Type::parse(std::vector<std::string>{LINE.begin() + KEYWORD_POS + 1, LINE.end()}));
        }

        TypeMap() = delete;
    };
}
