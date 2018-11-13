#pragma once

#include <functional>
#include <string>
#include <sparsehash/dense_hash_map>

namespace wiremap{
	std::size_t hasher(const std::string&);

    namespace detail{
        using KeyType = std::size_t;
        using Hasher = std::hash<KeyType>;

        struct KeyCompare{
            bool operator()(const KeyType& A, const KeyType& B)const{
                return A == B;
            }
        };
    }
}
