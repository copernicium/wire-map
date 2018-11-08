#pragma once

#include <functional> //TODO remove
#include "device_bases.hpp"
#include "function.hpp"
#include "map_util.hpp"
#include "object.hpp"

// A Result is a function that generates its output using a set of Parameters within the same device as it
namespace wiremap{
    struct Result: public detail::DeviceMemberBase{
    private:
        detail::KeyType source_device_key;
        google::dense_hash_map<detail::KeyType,detail::KeyType,detail::Hasher,detail::KeyCompare> source_parameter_hashes; //TODO Peripherals need Results too
		std::optional<Object> cache;
        std::function<Object(void)> update_function; //TODO use wire map function instead

        void setSourceDeviceKey(const detail::KeyType& D_KEY);

    public:
        const Object& get();

        Result(const std::function<Object(void)>&);

        Result() = delete;

        friend bool operator==(const Result&, const Result&);

		friend bool deepCompare(const Result&, const Result&);

        friend struct Device;
    };

    bool operator==(const Result&, const Result&);

	bool operator!=(const Result&, const Result&);

	bool deepCompare(const Result&, const Result&);
}
