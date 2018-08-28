#pragma once

#include <memory>
#include "object.hpp"
#include "device_bases.hpp"
#include "wiremap.hpp"

namespace wiremap{
    template<typename T>
    struct Parameter: public detail::ParameterBase{
        static_assert(detail::is_wiremap_object_v<T>,"Constant built from type not derived from detail::ObjectBase");
    protected:
        detail::KeyType source_device_hash;
        detail::KeyType source_result_hash;
        unsigned update_count;

    public:
        Parameter(const detail::KeyType& d_src, const detail::KeyType& r_src)noexcept: source_device_hash(d_src), source_result_hash(r_src), update_count(0){}

        Parameter() = delete;

        const std::shared_ptr<const detail::ResultBase> get()const noexcept{ //TODO update update_count
            return WireMap::get(source_device_hash).getResult(source_result_hash);
        }
    };
}
