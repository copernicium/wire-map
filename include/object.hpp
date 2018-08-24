#pragma once

#include "util.hpp"

namespace wiremap{
    namespace detail{
        struct ObjectBase{};

        template<typename T>
        inline constexpr bool is_wiremap_object_v = std::is_base_of_v<detail::ObjectBase,T>;

        template<typename T>
        struct Container: public detail::ObjectBase{
            T internal;
            std::size_t size;
        };
    }

    template<typename T, auto DefaultValue, typename... Attributes>
    struct Object: public detail::ObjectBase, public Attributes...{
        static_assert(!detail::is_specialization_of<T, detail::Container>::value, "Objects are not allowed to be of type detail::Container");
        static_assert(std::is_convertible_v<decltype(DefaultValue),T>, "Default value different than value type");

        using value_type = T;

        T value;
        T default_value;
        bool valid;

        Object(T v, T default_v)noexcept: value(v), default_value(default_v),valid(true){}
        Object(T v)noexcept: Object(v, DefaultValue){}
        Object()noexcept: default_value(DefaultValue),valid(false){}
    };

    namespace attributes{
        template<typename T>
        struct Integral{
            static_assert(std::is_integral_v<T>, "Integral defined with non-integral type");
        };
    }

    template<typename T>
    using Integral = Object<T, 0, attributes::Integral<T>>;

    using Bit = Integral<bool>;
    using Char = Integral<char>;
    using Byte = Integral<uint8_t>;
    using Word = Integral<uint16_t>;
    using DWord = Integral<uint32_t>;
    using QWord = Integral<uint64_t>;
    using Integer = Integral<long>;

    using Bool = Object<bool, false>;
    using Real = Object<double, 0>;

    template<typename T, std::size_t Size>
    struct List: public detail::Container<std::array<T, Size>>{
        static_assert(detail::is_wiremap_object_v<T>, "List value type not derived from detail::ObjectBase");

        List()noexcept:detail::Container<std::array<T, Size>>(){
            this->size = Size;
        }

        template<typename ArrT, typename = std::enable_if_t<std::is_convertible_v<ArrT, T>>>
        List(std::array<ArrT,Size> arr): List(){
            for(unsigned i = 0; i < this->size; i++){
                this->internal[i] = arr[i];
            }
        }
    };

    template<typename... Ts>
    struct Collection: public detail::Container<std::tuple<Ts...>>{
        static_assert(std::conjunction_v<std::is_base_of<detail::ObjectBase, Ts>...>, "Collection value type not derived from detail::ObjectBase");

        Collection()noexcept{
            this->size = sizeof...(Ts);
        }

    private:
        template<std::size_t i, typename... TupleTs>//, typename = std::enable_if_t<std::is_convertible_v<std::tuple_element<i,std::tuple<TupleTs...>>, std::tuple_element<i, std::tuple<Ts...>>>>> //TODO ensure all types can be converted
        constexpr void assignAll(const std::tuple<TupleTs...>& t){
            std::get<i>(this->internal) = std::get<i>(t);
            if constexpr((i + 1) < sizeof...(Ts)){
                assignAll<i + 1, TupleTs...>(t);
            }
        }

    public:
        template<typename... TupleTs, typename = std::enable_if_t<
                                          sizeof...(Ts) == sizeof...(TupleTs)
                                          >>
        Collection(const std::tuple<TupleTs...>& t): Collection(){
            assignAll<0,TupleTs...>(t);
        }
    };
}
