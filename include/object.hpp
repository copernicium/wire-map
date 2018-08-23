#pragma once

#include <array>
#include <optional>
#include <type_traits>

namespace wiremap{

    struct None{};

    namespace detail{

        template<typename T, template <typename...> class Template>
        struct is_specialization_of{
            using value = std::false_type;
        };

        template<template <typename...> class Template, typename ... Args>
        struct is_specialization_of<Template<Args...>, Template> {
            using value = std::true_type;
        };

        template<typename T, class ... Attributes>
        struct ObjectBase {
            using value_type = T;

            T value;
            bool valid;

            ObjectBase(T v)noexcept: value(v), valid(true){}
            ObjectBase()noexcept: valid(false){}
        };

        template<typename T>
        struct Container: public detail::ObjectBase<T>{
            std::size_t size;

            template<std::enable_if_t<std::is_base_of_v<std::tuple, T>>>
            Container(T v)noexcept: detail::ObjectBase<T>(v){
                using TupleTypes = typename T::Types;
                static_assert(std::conjunction_v<is_specialization_of<TupleTypes, ObjectBase>>, "Container value type not derived from detail::ObjectBase");
                size = std::tuple_size(v);
            }

            template<std::enable_if_t<std::is_base_of_v<std::array, T>>>
            Container(T v)noexcept: detail::ObjectBase<T>(v){
                static_assert(std::is_base_of_v<ObjectBase<T>, T::value_type>, "Container value type not derived from detail::ObjectBase");
                size = v.size();
            }

            Container()noexcept: detail::ObjectBase<T>(){
                static_assert(std::is_base_of_v<ObjectBase<T>, T>, "Container value type not derived from detail::ObjectBase");
                size = 0;
            }
        };
    }

    template<typename T, auto DefaultValue = None{}, class ... Attributes>
    struct Object: public detail::ObjectBase<T, Attributes...>{
        using S = decltype(DefaultValue);
        std::optional<T> default_value = DefaultValue;
        template<std::enable_if_t<std::is_base_of_v<std::tuple, T>>>
        Object(T v)noexcept: detail::ObjectBase<T>(v){
            using TupleTypes = typename T::Types;
            static_assert(std::conjunction_v<detail::is_specialization_of<TupleTypes, detail::ObjectBase>>, "Object value type not derived from detail::ObjectBase");
        }

        template<std::enable_if_t<std::is_base_of_v<std::array, T>>>
        Object(T v)noexcept: detail::ObjectBase<T>(v){
            static_assert(std::is_base_of_v<detail::ObjectBase<T>, T::value_type>, "Object value type not derived from detail::ObjectBase");
        }

        Object(T v, T default_v)noexcept: detail::ObjectBase<T>(v){
            static_assert(std::is_convertible_v<T,S>, "Default value different than value type");
            default_value = default_v;
        }
        Object(T v)noexcept: detail::ObjectBase<T>(v){
            static_assert(std::is_convertible_v<T,S>, "Default value different than value type");
            default_value = DefaultValue;
        }
        Object()noexcept: detail::ObjectBase<T>(){
            static_assert(std::is_convertible_v<T,S>, "Default value different than value type");
            default_value = DefaultValue;
        }
    };


    template<typename T>
    struct IntegralImpl {
    private:
        IntegralImpl()noexcept {
            static_assert(std::is_integral_v<T>, "Integral defined with non-integral type");
        }
    };

    template<typename T, auto DefaultValue>
    using Integral = Object<T, DefaultValue, IntegralImpl<T>>;
    using Bit = Integral<bool,  0>;
    using Char = Integral<char, 0>;
    using Byte = Integral<uint8_t, 0>;
    using Word = Integral<uint16_t, 0>;
    using DWord = Integral<uint32_t, 0>;
    using QWord = Integral<uint64_t, 0>;
    using Integer = Integral<long, 0>;

    using Bool = Object<bool, false>;
    using Real = Object<double, 0>;

    template<typename T, std::size_t Size>
    using List = Object<std::array<T, Size>, 0>;

    template<typename ...T>
    using Collection = Object<std::tuple<T...>, 0>;
}
