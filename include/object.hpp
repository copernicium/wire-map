#pragma once

#include <array>
#include <tuple>

namespace wiremap{
    namespace detail{
        struct ObjectBase{};

        template<typename T>
        struct MaybeObject: public ObjectBase{
            using value_type = T;

            T value;
            bool valid;

            MaybeObject(T v)noexcept: value(v), valid(true){}
            MaybeObject()noexcept: valid(false){}
        };

        template<typename T, std::size_t Size, bool ValueTypeTest>
        struct Container: public detail::MaybeObject<T>{
            std::size_t size;

            Container(T v)noexcept: detail::MaybeObject<T>(v){
                static_assert(ValueTypeTest, "Container value type not derived from detail::ObjectBase");
                size = Size;
            }

            Container()noexcept: detail::MaybeObject<T>(){
                static_assert(ValueTypeTest, "Container value type not derived from detail::ObjectBase");
                size = Size;
            }
        };
    }

    template<typename T, auto DefaultValue>
    struct Object: public detail::MaybeObject<T>{
        private:
        using DefaultValueType = decltype(DefaultValue);

        public:
        T default_value;

        Object(T v, T default_v)noexcept: detail::MaybeObject<T>(v){
            static_assert(std::is_convertible_v<T,DefaultValueType>, "Default value different than value type");
            default_value = default_v;
        }
        Object(T v)noexcept: detail::MaybeObject<T>(v){
            static_assert(std::is_convertible_v<T,DefaultValueType>, "Default value different than value type");
            default_value = DefaultValue;
        }
        Object()noexcept: detail::MaybeObject<T>(){
            static_assert(std::is_convertible_v<T,DefaultValueType>, "Default value different than value type");
            default_value = DefaultValue;
        }
    };

    template<typename T>
    struct Integral: public Object<T, 0> {
        Integral(T v, T default_v)noexcept: Object<T,0>(v, default_v){
            static_assert(std::is_integral_v<T>, "Integral defined with non-integral type");
        }
        Integral(T v)noexcept: Object<T,0>(v){
            static_assert(std::is_integral_v<T>, "Integral defined with non-integral type");
        }
        Integral()noexcept: Object<T,0>(){
            static_assert(std::is_integral_v<T>, "Integral defined with non-integral type");
        }
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
    using List = detail::Container<std::array<T, Size>, Size, std::is_base_of_v<detail::ObjectBase, T>>;

    template<typename ...T>
    using Collection = detail::Container<std::tuple<T...>, sizeof...(T), std::conjunction_v<std::is_base_of<detail::ObjectBase, T>...>>;
}