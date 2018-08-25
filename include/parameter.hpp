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
        KeyType source_device_hash;
        KeyType source_result_hash;
        unsigned update_count;

    public:
        Parameter(const KeyType& d_src, const KeyType& r_src)noexcept: source_device_hash(d_src), source_result_hash(r_src), update_count(0){}

        template<typename S>
        Parameter(Parameter<S>&) = delete;

        Parameter() = delete;

        const std::shared_ptr<detail::ResultBase>& get()const noexcept{
            return WireMap::get(source_device_hash).getResult(source_result_hash);
        }
    };
}
