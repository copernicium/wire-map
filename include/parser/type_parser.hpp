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

        std::vector<UnderlyingType> underlying_types; //TODO getters and setters to limit this depending on BaseType
    };

    std::optional<Type> parseType(const std::vector<std::string>&); //TODO replace all optional with exceptions
    std::optional<Type> parseType(const std::string&);
}
