#pragma once

#include <memory>
#include "device_bases.hpp"
#include "object.hpp"

namespace wiremap{
    template<typename T>
    struct Result: public ResultBase{
        static_assert(detail::is_wiremap_object_v<T>,"Constant built from type not derived from detail::ObjectBase");
    protected:
        unsigned update_count;
        std::shared_ptr<T> cache;

    public:
        const std::shared_ptr<T>& get()const{
            return cache;
        }

        Result(T v): update_count(0), cache(std::make_shared<T>(v)){}

        Result() = delete;

        template<typename T1, typename T2>
        friend bool operator==(const Result<T1>&, const Result<T2>&);
    };

    template<typename T1, typename T2>
    bool operator==(const Result<T1>& A, const Result<T2>& B){
        if(!std::is_same_v<T1,T2>){
            return false;
        }
        if(A.update_count != B.update_count){ //TODO compare this?
            return false;
        }
        if(A.cache != B.cache){ //TODO compare values not ptrs
            return false;
        }
        return true;
    }
}
