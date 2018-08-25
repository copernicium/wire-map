#pragma once

#include <functional>
#include <string>
#include <sparsehash/dense_hash_map>

namespace wiremap{
    const std::hash<std::string> hashstr;

    using KeyType = std::size_t;
    using Hasher = std::hash<KeyType>;

    struct KeyCompare{
        bool operator()(const KeyType& A, const KeyType& B)const{
            return A == B;
        }
    };
}
