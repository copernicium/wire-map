#pragma once

#include <string>
#include <vector>

namespace wiremap::parser{
    struct WireMapParser{
    private:
        static constexpr unsigned DEVICE_TYPE_POS = 0;
        static constexpr unsigned DEVICE_NAME_POS = 1;

    public:
        static void parse(const std::vector<std::string>&);
    };
}
