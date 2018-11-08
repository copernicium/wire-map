#pragma once

#include "device.hpp"
#include "function.hpp"

namespace wiremap{
    struct WireMap{
    private:
        static std::shared_ptr<google::dense_hash_map<detail::KeyType,Device,detail::Hasher,detail::KeyCompare>> devices;

    public:
        static void reset();

        template<typename... Members>
        static void add(const detail::KeyType& KEY, const Members&... DEVICE_MEMBERS)noexcept{
            if(devices == nullptr){
                reset();
            }
            assert(!exists(KEY));
            (*devices)[KEY] = Device(KEY, DEVICE_MEMBERS...);
        }

		template<typename... Members>
		static void add(const std::string& KEY, const Members&... DEVICE_MEMBERS)noexcept{
			add(hashstr(KEY), DEVICE_MEMBERS...);
		}

        static Device& get(const detail::KeyType&)noexcept;

        static Device& get(const std::string&)noexcept;

        static bool exists(const detail::KeyType&)noexcept;

        static bool exists(const std::string&)noexcept;

        WireMap() = delete;
    };

    struct Functions{
    private:
        static std::shared_ptr<google::dense_hash_map<detail::KeyType,Function,detail::Hasher,detail::KeyCompare>> functions;

    public:
        static Function& get(const detail::KeyType&)noexcept;

        Functions() = delete;
    };
}
