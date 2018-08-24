#pragma once

#include "object.hpp"

namespace wiremap{
    template<typename... Ts>
    struct Collection: public detail::Container<std::tuple<Ts...>>{
        static_assert(std::conjunction_v<std::is_base_of<detail::ObjectBase, Ts>...>, "Collection value type not derived from detail::ObjectBase");

        Collection()noexcept{
            this->_size = sizeof...(Ts);
        }

    private:
        template<std::size_t I, typename... TupleTs>//, typename = std::enable_if_t<std::is_convertible_v<std::tuple_element<i,std::tuple<TupleTs...>>, std::tuple_element<i, std::tuple<Ts...>>>>> //TODO ensure all types can be converted
        constexpr void assignAll(const std::tuple<TupleTs...>& t)noexcept{
            std::get<I>(this->_internal) = std::get<I>(t);
            if constexpr((I + 1) < sizeof...(Ts)){
                assignAll<I + 1, TupleTs...>(t);
            }
        }

    public:
        template<typename... TupleTs, typename = std::enable_if_t<sizeof...(Ts) == sizeof...(TupleTs)>>
        Collection(const std::tuple<TupleTs...>& t)noexcept: Collection(){
            assignAll<0,TupleTs...>(t);
        }

        ~Collection() = default;

        template<std::size_t I, typename... TupleTs>
        friend constexpr const std::tuple_element_t<I, std::tuple<TupleTs...>>& get(const Collection<TupleTs...>&)noexcept;

        template<std::size_t I, typename... TupleTs>
        friend constexpr std::tuple_element_t<I, std::tuple<TupleTs...>>& get(Collection<TupleTs...>&)noexcept;
    };

    template<std::size_t I, typename... Ts>
    constexpr const std::tuple_element_t<I, std::tuple<Ts...>>& get(const Collection<Ts...>& c)noexcept{
        return std::get<I>(c._internal);
    }

    template<std::size_t I, typename... Ts>
    constexpr std::tuple_element_t<I, std::tuple<Ts...>>& get(Collection<Ts...>& c)noexcept{
        return std::get<I>(c._internal);
    }
}
