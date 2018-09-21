#pragma once

#include "device.hpp"
#include "function.hpp"

namespace wiremap{
    struct WireMap{
    private:
        static std::shared_ptr<google::dense_hash_map<detail::KeyType,Device,detail::Hasher,detail::KeyCompare>> devices;

    public:
        static void add(const detail::KeyType& KEY, const Device& DEVICE)noexcept{
            if(devices == nullptr){
                devices = std::make_shared<google::dense_hash_map<detail::KeyType,Device,detail::Hasher,detail::KeyCompare>>();
                devices->set_empty_key(0);
            }
            assert(!exists(KEY));
            (*devices)[KEY] = Device(KEY, DEVICE);
        }

        static void add(const std::string& KEY, const Device& DEVICE)noexcept{
            add(hashstr(KEY), DEVICE);
        }

        static Device& get(const detail::KeyType& KEY)noexcept{
            assert(devices != nullptr && devices->find(KEY) != devices->end());
            return (*devices)[KEY];
        }

        static Device& get(const std::string& KEY)noexcept{
            return get(hashstr(KEY));
        }

        static bool exists(const detail::KeyType& KEY)noexcept{
            if(devices == nullptr){
                return false;
            }
            return devices->find(KEY) != devices->end();
        }

        static bool exists(const std::string& KEY)noexcept{
            return exists(hashstr(KEY));
        }

        WireMap() = delete;
    };

    struct Functions{
    private:
        static std::shared_ptr<google::dense_hash_map<detail::KeyType,Function,detail::Hasher,detail::KeyCompare>> functions;

    public:
        static Function& get(const detail::KeyType& KEY)noexcept{
            if(functions == nullptr){
                functions = std::make_shared<google::dense_hash_map<detail::KeyType,Function,detail::Hasher,detail::KeyCompare>>();
                functions->set_empty_key(0);
            }
            return (*functions)[KEY];
        }

        Functions() = delete;
    };
}
