#pragma once

#include "parser/device_parser.hpp"
#include <filesystem>

namespace wiremap::parser{
    struct Project{
    private:
        static constexpr std::string_view FILE_EXTENSION = ".wm";
        static constexpr std::string_view PROJECT_MAIN_FILE_NAME = "WireMap";

    public:
        static void parseFile(const std::filesystem::path&);

        static void parse(const std::filesystem::path&);
    };
}
