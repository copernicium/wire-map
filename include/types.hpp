#pragma once

#include "collection.hpp"
#include "constant.hpp"
#include "list.hpp"
#include "object.hpp"

namespace wiremap{
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
