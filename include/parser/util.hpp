#pragma once

#include <string>
#include <string_view>
#include <vector>

namespace wiremap::parser{
    namespace detail{
        constexpr std::string_view INDENT = "    ";
        constexpr char COMMENT_START = '#';
    }

    std::vector<std::string> splitLine(const std::string&);

    unsigned indentCount(const std::string&);
}
