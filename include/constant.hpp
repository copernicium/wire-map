#pragma once

#include "collection.hpp"
#include "device_bases.hpp"
#include "list.hpp"

namespace wiremap{
    template<typename T>
    struct Constant: public detail::ObjectBase, public detail::ConstantBase{
        static_assert(detail::is_wiremap_object_v<T>,"Constant built from type not derived from detail::ObjectBase");

    private:
        T value;

    public:
        template<typename V, typename = std::enable_if_t<detail::is_wiremap_object_v<V> == detail::is_specialization_of<V, Constant>::value>>
        Constant(const V& v)noexcept{
            value = T(v);
        }

        Constant() = delete;

        template<typename = std::enable_if<detail::is_object_specialization<T>::value>>
        constexpr const auto& get()const noexcept{
            return value.get();
        }

        template<typename = std::enable_if<detail::is_list_specialization<T>::value>>
        constexpr const auto& operator[](const std::size_t& pos)const noexcept{
            return value[pos];
        }

        template<std::size_t I, typename... Args>
        friend constexpr const std::tuple_element_t<I, std::tuple<Args...>>& get(const Constant<Collection<Args...>>&)noexcept;
    };

    template<std::size_t I, typename... Ts>
    constexpr const std::tuple_element_t<I, std::tuple<Ts...>>& get(const Constant<Collection<Ts...>>& c)noexcept{
        return get<I>(c.value);
    }
}
