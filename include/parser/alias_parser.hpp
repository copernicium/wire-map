#pragma once

#include <algorithm>
#include <memory>
#include <string>

#include "map_util.hpp"
#include "parser/type_parser.hpp"

namespace wiremap::parser{
    struct AliasMap{ //TODO add Real, Bool, etc by default
    private:
        static std::shared_ptr<google::dense_hash_map<detail::KeyType,Type,detail::Hasher,detail::KeyCompare>> aliases;

    public:
        static void add(const detail::KeyType& KEY, const Type& VALUE)noexcept{
            if(aliases == nullptr){
                aliases = std::make_shared<google::dense_hash_map<detail::KeyType,Type,detail::Hasher,detail::KeyCompare>>();
                aliases->set_empty_key(0);
            }
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
