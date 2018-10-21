#pragma once

#include <memory>
#include "device_bases.hpp"
#include "object.hpp"
#include "wiremap.hpp"
#include "result.hpp"

// A Parameter is a constant pointer to the value of a Result in the WireMap
namespace wiremap{
    template<typename T>
    struct Parameter: public detail::ParameterBase{
        static_assert(detail::is_wiremap_object_v<T>,"Constant built from type not derived from detail::ObjectBase");

    private:
		std::shared_ptr<Result<T>> source;

    public:
        Parameter(const detail::KeyType& source_device_key, const detail::KeyType& source_result_key)noexcept: source(
			std::dynamic_pointer_cast<Result<T>>(
				WireMap::get(source_device_key).getResult(source_result_key)
			)
		){}

        Parameter(const std::string& d_src, const std::string& r_src)noexcept: Parameter(hashstr(d_src),hashstr(r_src)){}

        Parameter() = delete;

        const T& get()const noexcept{
			return source->get();
        }

        template<typename>
        friend struct Result;
    };
}
