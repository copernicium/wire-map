#include "parser/device_parser.hpp"
#include "parser/type_parser.hpp"

namespace wiremap::parser{
    std::shared_ptr<google::dense_hash_map<wiremap::detail::KeyType,TypeNode,wiremap::detail::Hasher,wiremap::detail::KeyCompare>> TypeMap::types = nullptr;
    std::shared_ptr<google::dense_hash_map<wiremap::detail::KeyType,DeviceNode,wiremap::detail::Hasher,wiremap::detail::KeyCompare>> DeviceNodes::device_nodes = nullptr;
}
