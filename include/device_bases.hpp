#pragma once

#include <memory>

namespace wiremap::detail{
    struct DeviceMemberBase{
        virtual ~DeviceMemberBase() = default;
    };

    struct ParameterBase: public DeviceMemberBase{
        virtual ~ParameterBase() = default;
    };

    struct ConstantBase: public DeviceMemberBase{
        virtual ~ConstantBase() = default;
    };

    struct ResultBase: public DeviceMemberBase{
        virtual ~ResultBase() = default;
    };
}
