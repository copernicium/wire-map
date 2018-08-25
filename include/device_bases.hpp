#pragma once

#include <memory>

namespace wiremap::detail{
    struct ParameterBase{
        virtual ~ParameterBase() = default;
    };

    struct ConstantBase{
        virtual ~ConstantBase() = default;
    };

    struct ResultBase{
        virtual ~ResultBase() = default;
    };
}
