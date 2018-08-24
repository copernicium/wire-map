#pragma once

#include <array>
#include <optional>
#include <type_traits>
#include <tuple>

namespace wiremap{

    struct None{};

    namespace detail{
        template<typename T, template <typename...> typename Template>
        struct is_specialization_of: public std::false_type{};

        template<template <typename...> typename Template, typename... Args>
        struct is_specialization_of<Template<Args...>, Template>: public std::true_type{};

        template<typename T>
        struct is_std_array: public std::false_type{};

        template<typename T, std::size_t Size>
        struct is_std_array<std::array<T, Size>>: public std::true_type{};

        template<typename T>
        inline constexpr bool is_std_array_v = is_std_array<T>::value;

        template <bool AllDerivedTypes, typename... T>
        struct check_tuple;

        template<>
        struct check_tuple<true>: std::true_type{};

        template<>
        struct check_tuple<false>: std::false_type{};

        template<bool AllDerivedTypes, typename Base, typename First>
        struct check_tuple<AllDerivedTypes, Base, First>: check_tuple<AllDerivedTypes && std::is_base_of_v<Base, First>>{};

        template<bool AllDerivedTypes, typename Base, typename First, typename... Rest>
        struct check_tuple<AllDerivedTypes, Base, First, Rest...>: check_tuple<AllDerivedTypes && std::is_base_of_v<Base, First>, Base, Rest...>{};

        template<typename Base, typename... Ts>
        struct check_tuple_types;

        template<typename Base, typename... Ts>
        struct check_tuple_types<Base, std::tuple<Ts...>> : check_tuple<true, Base, Ts...>{};

        template<typename T>
        struct array_size;

        template<typename T, std::size_t Size>
        struct array_size< std::array<T, Size>>: public std::integral_constant<std::size_t, Size>{};

        template<typename T>
        inline constexpr std::size_t array_size_v = array_size<T>::value;

        struct ObjectBase{};

        template<typename T>
        struct Container: public detail::ObjectBase{
            T internal;
            std::size_t size;

            Container()noexcept{
                if constexpr (is_specialization_of<T, std::tuple>::value){
                    static_assert(check_tuple_types<ObjectBase, T>::value, "Container value type not derived from detail::ObjectBase");
                    size = std::tuple_size_v<T>;
                } else if(is_std_array_v<T>){
                    static_assert(std::is_base_of_v<ObjectBase, typename T::value_type>, "Container value type not derived from detail::ObjectBase");
                    size = array_size_v<T>;
                }
            }

            Container(T v)noexcept:Container(){
                internal = v;
            }
        };
    }

    template<typename T, auto DefaultValue>
    struct Object: public detail::ObjectBase{
    protected:
        static_assert(!detail::is_specialization_of<T, detail::Container>::value, "Objects are not allowed to be of type detail::Container");
        static_assert(std::is_convertible_v<T,decltype(DefaultValue)>, "Default value different than value type");

    public:
        using value_type = T;

        T value;
        T default_value;
        bool valid;

        Object(T v, T default_v)noexcept: value(v), default_value(default_v),valid(true){}
        Object(T v)noexcept: Object(v, DefaultValue){}
        Object()noexcept: default_value(DefaultValue),valid(false){}
    };

    template<typename T>
    struct Integral: public Object<T, 0>{ //TODO look into integrating as attributes
    protected:
        static_assert(std::is_integral_v<T>, "Integral defined with non-integral type");

    public:
        Integral(T v)noexcept: Object<T, 0>(v){}
        Integral()noexcept: Object<T, 0>(){}
    };

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
    using List = detail::Container<std::array<T, Size>>;

    template<typename... Ts>
    using Collection = detail::Container<std::tuple<Ts...>>;
}
