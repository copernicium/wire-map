#pragma once

#include "parser/tokenizer.hpp"

namespace wiremap::parser{
    struct WireMapParser{
    private:
        static constexpr unsigned DEVICE_TYPE_POS = 0;
        static constexpr unsigned DEVICE_NAME_POS = 1;

		static constexpr unsigned MEMBER_NAME_POS = 0;
		static constexpr unsigned MEMBER_ASSIGNMENT_OPERATOR_POS = 1;

		static constexpr unsigned PARAMETER_SOURCE_DEVICE_POS = 2;
		static constexpr unsigned PARAMETER_SOURCE_SEPARATOR_POS = 3;
		static constexpr unsigned PARAMETER_SOURCE_RESULT_POS = 4;

    public:
        static void parse(const Lines&);
    };
}
