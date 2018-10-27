#pragma once

#include <string>
#include <string_view>
#include <vector>

namespace wiremap::parser{
    struct WireMapParser{
    private:
        static constexpr unsigned DEVICE_TYPE_POS = 0;
        static constexpr unsigned DEVICE_NAME_POS = 1;

		static constexpr unsigned MEMBER_NAME_POS = 0;
		static constexpr unsigned MEMBER_ASSIGNMENT_OPERATOR_POS = 1;

		static constexpr std::string_view PARAMETER_SOURCE_OPERATOR = "<-";
		static constexpr std::string_view PARAMETER_SOURCE_SEPARATOR_OPERATOR = ".";
		static constexpr unsigned PARAMETER_SOURCE_DEVICE_POS = 2;
		static constexpr unsigned PARAMETER_SOURCE_SEPARATOR_POS = 3;
		static constexpr unsigned PARAMETER_SOURCE_RESULT_POS = 4;

		static constexpr std::string_view CONSTANT_ASSIGNMENT_OPERATOR = "=";

    public:
        static void parse(const std::vector<std::string>&);
    };
}
