#pragma once

#include <cassert>
#include "util.hpp"

namespace wiremap{
    namespace attributes{
        template<typename T, typename... AttributeChecks>
        struct Attribute{
            static void verify(const T&){}
        };

        template<typename T, typename First, typename... AttributeChecks>
        struct Attribute<T, First, AttributeChecks...>{
            static void verify(const T& v){
                First::verify(v);
                Attribute<T, AttributeChecks...>::verify(v);
            }
        };
    }

    namespace detail{
        struct ObjectBase{
            virtual ~ObjectBase() = default;
        };

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

        template<typename T, auto DefaultValue,  typename... Attributes>
        struct Object: public ObjectBase, public Attributes...{
            static_assert(!detail::is_specialization_of<T, detail::Container>::value, "Objects are not allowed to be of type detail::Container");
            static_assert(std::is_convertible_v<decltype(DefaultValue),T>, "Default value different than value type");

            using value_type = T;

        protected:
            T value;
            T default_value;
            bool valid;

        public:
            Object(const T& v, const T& default_v)noexcept: value(v), default_value(default_v),valid(true){
                attributes::Attribute<T,Attributes...>::verify(v);
                attributes::Attribute<T,Attributes...>::verify(default_v);
            }

            Object(const T& v)noexcept: Object(v, DefaultValue){
                attributes::Attribute<T,Attributes...>::verify(v);
            }

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

            template<typename CompT, auto CompDefaultValue, typename... CompAttributes>
                bool operator==(const Object<CompT,CompDefaultValue,CompAttributes...>& B){
                if(!std::is_same_v<decltype(*this),decltype(B)>){
                    return false;
                }
                if(default_value != B.default_value){
                    return false;
                }
                if(valid != B.valid){
                    return false;
                }
                if(valid && value != B.value){
                    return false;
                }
                return true;
            }
        };
    }

    namespace detail{
        template<typename T>
        struct is_object_specialization: public std::false_type{};

        template<typename T, auto D, typename... Attributes>
        struct is_object_specialization<Object<T, D, Attributes...>>: public std::true_type{};
    }

    namespace attributes{
        template<typename T>
        struct Integral{
            static_assert(std::is_integral_v<T>, "Integral defined with non-integral type");
            static constexpr void verify(const T&)noexcept{}
        };

        template<typename T,auto DefaultValue, decltype(DefaultValue) Begin, decltype(DefaultValue) End>
        struct InRange{
            static_assert(Begin <= DefaultValue && DefaultValue <= End);

            static constexpr void verify(const T& value)noexcept{
                assert(Begin <= value && value <= End); //TODO invalidate data instead? throw?
            }
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
