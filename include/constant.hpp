#pragma once

#include "object.hpp"

namespace wiremap{
    template<typename T>
    struct Constant: detail::ObjectBase{
        static_assert(detail::is_wiremap_object_v<T>,"Constant built from type not derived from detail::ObjectBase");

        T value;

        template<typename V, typename = std::enable_if_t<detail::is_wiremap_object_v<V> == detail::is_specialization_of<V, Constant>::value>>
        Constant(V v){
            value = T(v);
        }

        Constant() = delete;
    };
}
