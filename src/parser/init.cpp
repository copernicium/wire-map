#include "parser/alias_parser.hpp"
#include "parser/device_parser.hpp"

namespace wiremap::parser{
    std::shared_ptr<google::dense_hash_map<detail::KeyType,Type,detail::Hasher,detail::KeyCompare>> AliasMap::aliases = nullptr;
    std::shared_ptr<google::dense_hash_map<detail::KeyType,DeviceNode,detail::Hasher,detail::KeyCompare>> DeviceNodes::device_nodes = nullptr;
}
