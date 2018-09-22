#pragma once

#include <algorithm>
#include <memory>
#include <string>

#include "map_util.hpp"
#include "parser/type_parser.hpp"

namespace wiremap::parser{
    struct AliasMap{ //TODO rename to TypeMap and move to types_parser
        static constexpr unsigned KEYWORD_POS = 1;
        static constexpr std::string_view KEYWORD = "as";

    private:
        static std::shared_ptr<google::dense_hash_map<detail::KeyType,Type,detail::Hasher,detail::KeyCompare>> aliases;

    public:
        static void reset(){
            aliases = std::make_shared<google::dense_hash_map<detail::KeyType,Type,detail::Hasher,detail::KeyCompare>>();
            aliases->set_empty_key(0);
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

        static void add(const detail::KeyType& KEY, const Type& VALUE)noexcept{
            if(aliases == nullptr){
                reset();
            }
            assert(!exists(KEY));
            aliases->insert(std::make_pair(KEY, VALUE));
        }

        static void add(const std::string& KEY, const Type& VALUE)noexcept{
            add(hashstr(KEY),VALUE);
        }

        static Type& get(const detail::KeyType& KEY)noexcept{
            assert(aliases != nullptr && aliases->find(KEY) != aliases->end());
            return (*aliases)[KEY];
        }

        static Type& get(const std::string& KEY)noexcept{
            return get(hashstr(KEY));
        }

        static bool exists(const detail::KeyType& KEY)noexcept{
            if(aliases == nullptr){
                return false;
            }
            return aliases->find(KEY) != aliases->end();
        }

        static bool exists(const std::string& KEY)noexcept{
            return exists(hashstr(KEY));
        }

        AliasMap() = delete;
    };
}
