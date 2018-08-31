#pragma once

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

namespace wiremap::parser{
    struct TypeMap{
    private:
        static std::shared_ptr<std::vector<std::string>> types;

    public:
        static bool exists(const std::string& NAME)noexcept{
            if(types == nullptr){
                return false;
            }
            return std::find(types->begin(), types->end(), NAME) != types->end();
        }

        static void add(const std::string& NAME)noexcept{
            if(types == nullptr){
                types = std::make_shared<std::vector<std::string>>();
            }
            types->push_back(NAME);
        }

        TypeMap() = delete;
    };



}
