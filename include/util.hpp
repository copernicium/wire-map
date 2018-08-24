#pragma once

#include <array>
#include <type_traits>
#include <tuple>

namespace wiremap{
    namespace detail{
        template<typename T, template <typename...> typename Template>
        struct is_specialization_of: public std::false_type{};

        template<template <typename...> typename Template, typename... Args>
        struct is_specialization_of<Template<Args...>, Template>: public std::true_type{};

        template<typename T>
        struct is_array_specialization: public std::false_type{};

        template<typename T, std::size_t Size>
        struct is_array_specialization<std::array<T, Size>>: public std::true_type{};

        template<typename T>
        inline constexpr bool is_array_specialization_v = is_array_specialization<T>::value;

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
        struct array_size: public std::integral_constant<std::size_t, 0>{};

        template<typename T, std::size_t Size>
        struct array_size< std::array<T, Size>>: public std::integral_constant<std::size_t, Size>{};

        template<typename T>
        inline constexpr std::size_t array_size_v = array_size<T>::value;
    }
}
