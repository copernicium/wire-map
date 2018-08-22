#pragma once

#include <array>

namespace wiremap{
    template<typename T>
    struct Object{
        T value;
        T default_value; //TODO
        bool valid;

        Object(T v,T default_v):value(v),default_value(default_v),valid(true){}
        Object(T v)noexcept:value(v), valid(true){}
        Object()noexcept:valid(false){}
    };

    template<typename T,
             typename = std::enable_if<std::is_integral_v<T>>>
    struct Integral : Object<T> {};

    using Bit = Integral<bool>;
    using Char = Integral<char>;
    using Byte = Integral<uint8_t>;
    using Word = Integral<uint16_t>;
    using DWord = Integral<uint32_t>;
    using QWord = Integral<uint64_t>;
    using Integer = Integral<long>;

    using Bool = Object<bool>;
    using Real = Object<double>;

    template<typename T, std::size_t Size>
    using List = Object<std::array<Object<T>, Size>>;
    template<typename ... T>
    using Collection = Object<std::tuple<Object<T>...>>;
}
