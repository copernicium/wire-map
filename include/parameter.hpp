#pragma once

#include "device_bases.hpp"
#include "wiremap.hpp"
#include "result.hpp"

// A Parameter is a constant pointer to the value of a Result in the WireMap
namespace wiremap{
    struct Parameter: public detail::DeviceMemberBase{
    private:
		detail::KeyType source_device_key;
		detail::KeyType source_result_key;
		std::shared_ptr<Result> source;

    public:
        Parameter(const detail::KeyType&, const detail::KeyType&)noexcept;

        Parameter(const std::string&, const std::string&)noexcept;

        Parameter() = delete;

        const Object& get()noexcept;

        friend struct Result;
    };
}
