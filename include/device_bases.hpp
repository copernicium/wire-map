#pragma once

#include <memory>
#include "map_util.hpp"

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
        virtual void setSourceDeviceKey(const detail::KeyType&) = 0;

        virtual ~ResultBase() = default;
    };
}
