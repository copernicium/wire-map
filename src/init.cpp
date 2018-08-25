#include "wiremap.hpp"

namespace wiremap{
    std::shared_ptr<google::dense_hash_map<KeyType,Device,Hasher,KeyCompare>> WireMap::devices = nullptr;
}
