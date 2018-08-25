#pragma once

#include <optional>
#include <string>
// #include <sparsehash/dense_hash_map>

namespace wiremap::parser{
    using ParseInput = std::string;

    template<typename R>
    using ParseResult = std::optional<std::pair<R,std::string>>;
}
