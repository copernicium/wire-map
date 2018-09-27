#pragma once

#include <algorithm>
#include <memory>
#include <string>

#include "map_util.hpp"
#include "parser/type_parser.hpp"
#include "parser/util.hpp"

namespace wiremap::parser{
    struct AliasMap{ //TODO rename to TypeMap and move to types_parser
        static constexpr std::string_view KEYWORD = "as";
        static constexpr unsigned KEYWORD_POS = 1;
        static constexpr unsigned MINIMUM_LINE_SIZE = 3;

    private:
        static std::shared_ptr<google::dense_hash_map<wiremap::detail::KeyType,Type,wiremap::detail::Hasher,wiremap::detail::KeyCompare>> aliases;

    public:
        static bool isAliasIdentifier(const std::vector<std::string>& LINE){
            return LINE.size() >= MINIMUM_LINE_SIZE && LINE[KEYWORD_POS] == KEYWORD;
        }

        static void reset(){
            aliases = std::make_shared<google::dense_hash_map<wiremap::detail::KeyType,Type,wiremap::detail::Hasher,wiremap::detail::KeyCompare>>();
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

        static void add(const wiremap::detail::KeyType& KEY, const Type& VALUE)noexcept{
            if(aliases == nullptr){
                reset();
            }
            assert(!exists(KEY));
            (*aliases)[KEY] = VALUE;
        }

        static void add(const std::string& KEY, const Type& VALUE)noexcept{
            add(hashstr(KEY),VALUE);
        }

        static Type& get(const wiremap::detail::KeyType& KEY)noexcept{
            assert(aliases != nullptr && aliases->find(KEY) != aliases->end());
            return (*aliases)[KEY];
        }

        static Type& get(const std::string& KEY)noexcept{
            return get(hashstr(KEY));
        }

        static bool exists(const wiremap::detail::KeyType& KEY)noexcept{
            if(aliases == nullptr){
                return false;
            }
            return aliases->find(KEY) != aliases->end();
        }

        static bool exists(const std::string& KEY)noexcept{
            return exists(hashstr(KEY));
        }

        static void parse(const std::vector<std::string>& LINE){
            if(LINE.empty() || !isAliasIdentifier(LINE)){
                return;
            }
            if(exists(LINE.front())){
                exit(EXIT_FAILURE); //TODO error, redefinition
            }
            add(LINE.front(), Type::parse(std::vector<std::string>{LINE.begin() + KEYWORD_POS + 1, LINE.end()}));
        }

        AliasMap() = delete;
    };
}
