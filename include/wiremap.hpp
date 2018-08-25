#pragma once

#include "device.hpp"

namespace wiremap{
    struct WireMap{
    private:
        static std::shared_ptr<google::dense_hash_map<detail::KeyType,Device,detail::Hasher,detail::KeyCompare>> devices;

    public:
        static Device& get(const detail::KeyType& I)noexcept{
            if(devices == nullptr){
                devices = std::make_shared<google::dense_hash_map<detail::KeyType,Device,detail::Hasher,detail::KeyCompare>>();
                devices->set_empty_key(0);
            }
            return (*devices)[I];
        }

        WireMap() = delete;
    };
}
