#pragma once

namespace wiremap::detail{
    struct DeviceMemberBase{
        virtual ~DeviceMemberBase() = default;
    };

    struct ConstantBase: public DeviceMemberBase{
        virtual ~ConstantBase() = default;
    };
}
