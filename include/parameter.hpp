#pragma once

#include <memory>
#include "device_bases.hpp"
#include "object.hpp"
#include "wiremap.hpp"

namespace wiremap{
    template<typename T>
    struct Parameter: public detail::ParameterBase{
        static_assert(detail::is_wiremap_object_v<T>,"Constant built from type not derived from detail::ObjectBase");

    private:
        detail::KeyType source_device_key;
        detail::KeyType source_result_key;
        unsigned update_count;

        void updateCount(){
            update_count = WireMap::get(source_device_key).getResult(source_result_key)->getUpdateCount();
        }

    public:
        Parameter(const detail::KeyType& d_src, const detail::KeyType& r_src)noexcept: source_device_key(d_src), source_result_key(r_src), update_count(0){}

        Parameter() = delete;

        const std::shared_ptr<const detail::ResultBase> get()const noexcept{
            return WireMap::get(source_device_key).getResult(source_result_key);
        }

        template<typename>
        friend struct Result;
    };
}
