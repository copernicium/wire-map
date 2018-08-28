#pragma once
#include "parameter.hpp"
#include "result.hpp"

namespace wiremap{
    template<typename T>
    const Result<T>& getResult(const Parameter<T>& p){
        return *std::dynamic_pointer_cast<const Result<T>>(p.get());
    }
}
