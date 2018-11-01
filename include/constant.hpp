#pragma once

#include "device_bases.hpp"

// A Constant is a constant value
namespace wiremap{
    template<typename T>
    struct Constant: public detail::ObjectBase, public detail::ConstantBase{
        static_assert(detail::is_wiremap_primitive_v<T>,"Constant built from type not derived from detail::ObjectBase");

    private:
        T value;

    public:
        template<typename V, typename = std::enable_if_t<detail::is_wiremap_primitive_v<V> == detail::is_specialization_of<V, Constant>::value>>
        Constant(const V& v)noexcept{
            value = T(v);
        }

        Constant() = delete;

        constexpr const auto& get()const noexcept{
            return value.get();
        }
    };
}
