#pragma once

#include <memory>
#include "object.hpp"
#include "device_bases.hpp"
#include "wiremap.hpp"

namespace wiremap{
    template<typename T>
    struct Parameter{
        static_assert(detail::is_wiremap_object_v<T>,"Constant built from type not derived from detail::ObjectBase");
    protected:
        std::size_t source_device_hash;
        std::size_t source_result_hash;
        unsigned update_count;

    public:
        Parameter(const std::size_t& d_src, const std::size_t& r_src)noexcept: source_device_hash(d_src), source_result_hash(r_src), update_count(0){}

        template<typename S>
        Parameter(Parameter<S>&) = delete;

        Parameter() = delete;

        const std::shared_ptr<ResultBase>& get()const noexcept{
            return WireMap::get(source_device_hash).getResult(source_result_hash);
        }
    };
}
