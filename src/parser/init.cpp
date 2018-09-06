#include "parser/alias_parser.hpp"

namespace wiremap::parser{
    std::shared_ptr<google::dense_hash_map<detail::KeyType,Type,detail::Hasher,detail::KeyCompare>> AliasMap::aliases = nullptr;
}
