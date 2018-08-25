#include "wiremap.hpp"

namespace wiremap{
    std::shared_ptr<google::dense_hash_map<detail::KeyType,Device,detail::Hasher,detail::KeyCompare>> WireMap::devices = nullptr;
}
