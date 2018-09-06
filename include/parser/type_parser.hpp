#pragma once

#include <optional>
#include <string>
#include <vector>

namespace wiremap::parser{
    struct Type{
        enum class BaseType{
            OBJECT,
            LIST,
            COLLECTION
        };

        enum class UnderlyingType{
            BIT,
            CHAR,
            BYTE,
            WORD,
            DWORD,
            QWORD,
            INTEGER,
            BOOL,
            REAL
        };

        BaseType base_type;

        std::vector<UnderlyingType> underlying_types;
    };

    std::optional<Type> parseType(const std::string&);
}
