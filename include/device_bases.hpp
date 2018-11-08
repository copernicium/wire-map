#pragma once

#include <memory>
#include "map_util.hpp"

namespace wiremap::detail{
    struct DeviceMemberBase{
        virtual ~DeviceMemberBase() = default;
    };

    struct ConstantBase: public DeviceMemberBase{
        virtual ~ConstantBase() = default;
    };
}
