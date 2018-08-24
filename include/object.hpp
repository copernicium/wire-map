#pragma once

#include <cassert>
#include "util.hpp"

namespace wiremap{
    namespace detail{
        struct ObjectBase{};

        template<typename T>
        inline constexpr bool is_wiremap_object_v = std::is_base_of_v<detail::ObjectBase,T>;

        template<typename T>
        struct Container: public detail::ObjectBase{
        protected:
            T _internal;
            std::size_t _size;

        public:
            constexpr std::size_t size()const noexcept{
                return _size;
            }
        };

        template<typename T, auto DefaultValue, typename... Attributes>
        struct Object: public ObjectBase, public Attributes...{
            static_assert(!detail::is_specialization_of<T, detail::Container>::value, "Objects are not allowed to be of type detail::Container");
            static_assert(std::is_convertible_v<decltype(DefaultValue),T>, "Default value different than value type");

            using value_type = T;

        protected:
            T value;
            T default_value;
            bool valid;

        public:
            Object(T v, T default_v)noexcept: value(v), default_value(default_v),valid(true){}
            Object(T v)noexcept: Object(v, DefaultValue){}
            Object()noexcept: default_value(DefaultValue),valid(false){}

            constexpr const T& getDefault()const noexcept{
                return default_value;
            }

            constexpr const T& require()const noexcept{
                if(valid){
                    return value;
                }
                return default_value;
            }

            constexpr const T& get()const noexcept{
                assert(valid);
                return value;
            }

            constexpr T& get()noexcept{
                assert(valid);
                return value;
            }

            constexpr operator bool()const noexcept{
                return valid;
            }
        };
    }

    namespace detail{
        template<typename T>
        struct is_object_specialization: public std::false_type{};

        template<typename T, auto D, typename... Args>
        struct is_object_specialization<Object<T, D, Args...>>: public std::true_type{};
    }

    namespace attributes{
        template<typename T>
        struct Integral{
            static_assert(std::is_integral_v<T>, "Integral defined with non-integral type");
        };
    }

    template<typename T>
    using Integral = detail::Object<T, 0, attributes::Integral<T>>;

    using Bit = Integral<bool>;
    using Char = Integral<char>;
    using Byte = Integral<uint8_t>;
    using Word = Integral<uint16_t>;
    using DWord = Integral<uint32_t>;
    using QWord = Integral<uint64_t>;
    using Integer = Integral<long>;

    using Bool = detail::Object<bool, false>;
    using Real = detail::Object<double, 0>;
}
