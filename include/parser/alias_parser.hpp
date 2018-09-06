#pragma once

#include <algorithm>
#include <memory>
#include <string>

#include "map.hpp"
#include "parser/type_parser.hpp"

namespace wiremap::parser{
    struct AliasMap{
    private:
        static std::shared_ptr<google::dense_hash_map<detail::KeyType,Type,detail::Hasher,detail::KeyCompare>> aliases;

    public:
        static bool exists(const detail::KeyType& NAME)noexcept{
            if(aliases == nullptr){
                return false;
            }
            return aliases->find(NAME) != aliases->end();
        }

        static void add(const detail::KeyType& NAME, const Type& type)noexcept{
            if(aliases == nullptr){
                aliases = std::make_shared<google::dense_hash_map<detail::KeyType,Type,detail::Hasher,detail::KeyCompare>>();
                aliases->set_empty_key(0);
            }
            aliases->insert(std::make_pair(NAME, type));
        }

        AliasMap() = delete;
    };
}
