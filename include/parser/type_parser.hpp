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
    private:
        static constexpr std::string_view COLLECTION_KEYWORD = "Collection";
        static constexpr std::string_view LIST_KEYWORD = "List";
        static constexpr std::string_view CONTAINER_TYPE_SPECIFIER = "of";

        BaseType base_type;

        std::vector<UnderlyingType> underlying_types;

        unsigned list_size;

        static Type parseObject(const std::string&);
        static Type parseList(const std::vector<std::string>&);
        static Type parseCollection(const std::vector<std::string>&);
    public:

        BaseType getBaseType()const;

        UnderlyingType getUnderlyingType()const;

        std::vector<UnderlyingType> getUnderlyingTypes()const;

        unsigned getListSize()const;

        static Type parse(const std::vector<std::string>&);
        static Type parse(const std::string&);

        Type();
        Type(const UnderlyingType&);
        Type(const UnderlyingType&, const unsigned&);
        Type(const std::vector<UnderlyingType>&);

        std::string toString()const;

        friend bool operator==(const Type&, const Type&);
    };

    bool operator==(const Type&, const Type&);

    std::string asString(const Type::BaseType&);
}
