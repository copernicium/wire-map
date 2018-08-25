#pragma once

#include "device.hpp"

namespace wiremap{
    struct WireMap{
    private:
        // static_assert(Hasher(576) == 576);//TODO

        static std::shared_ptr<google::dense_hash_map<KeyType,Device,Hasher,KeyCompare>> devices;

    public:
        static Device& get(const KeyType& I)noexcept{
            if(devices == nullptr){
                devices = std::make_shared<google::dense_hash_map<KeyType,Device,Hasher,KeyCompare>>();
                devices->set_empty_key(0);
            }
            return (*devices)[I];
        }

        WireMap() = delete;
    };
}
