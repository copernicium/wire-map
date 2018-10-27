#pragma once

#include <memory>
#include "device_bases.hpp"
#include "wiremap.hpp"
#include "result.hpp"

// A Parameter is a constant pointer to the value of a Result in the WireMap
namespace wiremap{
    template<typename T>
    struct Parameter: public detail::ParameterBase{
    private:
		detail::KeyType source_device_key;
		detail::KeyType source_result_key;
		std::shared_ptr<Result<T>> source;

    public:
        Parameter(const detail::KeyType& device_key, const detail::KeyType& result_key)noexcept: source_device_key(device_key), source_result_key(result_key), source(nullptr){}

        Parameter(const std::string& d_src, const std::string& r_src)noexcept: Parameter(hashstr(d_src),hashstr(r_src)){}

        Parameter() = delete;

        const T& get()noexcept{
			if(source == nullptr){
				source = std::dynamic_pointer_cast<Result<T>>(
					WireMap::get(source_device_key).getResult(source_result_key)
				);
			}
			return source->get();
        }

        template<typename>
        friend struct Result;
    };
}
