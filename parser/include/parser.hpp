#pragma once

#include <optional>
#include <pair>
#include <string>

namespace wiremap::parser{
    using ParseInput = std::string;

    template<typename R>
    using ParseResult = std::optional<std::pair<R,std::string>>;
}
