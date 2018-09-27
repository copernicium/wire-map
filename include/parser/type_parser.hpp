#pragma once

#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

namespace wiremap::parser{
    struct Type{
        enum class BaseType{
            PRIMITIVE,
            LIST,
            COLLECTION
        };

        enum class PrimitiveType{
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

        using UnderlyingListType = std::pair<std::shared_ptr<Type>, std::size_t>;

        using UnderlyingCollectionType = std::vector<std::shared_ptr<Type>>;

        using UnderlyingType = std::variant<PrimitiveType, UnderlyingListType, UnderlyingCollectionType>;

    private:
        static constexpr unsigned CONTAINER_KEYWORD_POS = 0;
        static constexpr unsigned CONTAINER_SPECIFIER_POS = 1;
        static constexpr unsigned LIST_SIZE_POS = 2;
        static constexpr std::string_view COLLECTION_KEYWORD = "Collection";
        static constexpr std::string_view COLLECTION_SEPARATOR = ",";
        static constexpr std::string_view LIST_KEYWORD = "List";
        static constexpr std::string_view CONTAINER_TYPE_SPECIFIER = "of";

        static bool isList(const std::vector<std::string>&);

        static bool isCollection(const std::vector<std::string>&);

        BaseType base_type;

        UnderlyingType underlying_type;

        static Type parseObject(const std::string&);
        static Type parseList(const std::vector<std::string>&);
        static Type parseCollection(const std::vector<std::string>&);
    public:

        BaseType getBaseType()const;

        PrimitiveType getObjectType()const;

        unsigned getListSize()const;

        Type getListType()const;

        std::vector<Type> getCollectionTypes()const;

        static Type parse(const std::vector<std::string>&);
        static Type parse(const std::string&);

        Type();
        Type(const PrimitiveType&);
        Type(const UnderlyingListType&);
        Type(const UnderlyingCollectionType&);

        std::string toString()const;

        friend bool operator==(const Type&, const Type&);
    };

    bool operator==(const Type&, const Type&);
    bool operator!=(const Type&, const Type&);

    std::string asString(const Type::BaseType&);
}
