#pragma once

#include <functional> //TODO remove
#include <memory>
#include "device_bases.hpp"
#include "function.hpp"
#include "object.hpp"
#include "wiremap.hpp"

namespace wiremap{
    template<typename T>
    struct Result: public detail::ResultBase{
        static_assert(detail::is_wiremap_object_v<T>,"Constant built from type not derived from detail::ObjectBase");

    private:
        detail::KeyType source_device_key;
        google::dense_hash_map<detail::KeyType,detail::KeyType,detail::Hasher,detail::KeyCompare> source_parameter_hashes;
        unsigned update_count;
		std::optional<T> cache;
        std::function<T(void)> update_function; //TODO use wire map function instead

        void setSourceDeviceKey(const detail::KeyType& D_KEY){
            source_device_key = D_KEY;
        }

    public:
        unsigned getUpdateCount()const{
            return update_count;
        }

        const T& get(){
            if(!cache.has_value()){
                cache = update_function();
            }
            for(const std::pair<detail::KeyType, detail::KeyType>& source_parameter: source_parameter_hashes){
                /*
                TODO check if results parameters point to have been updated
                if(update case){
                    update_count++;
                    auto param = WireMap::get(source_device_hash).getParameter(source_parameter);
                    param.updateCount()
                    cache = update_function(param);
                }
                */
            }
            return cache.value();
        }

        Result(const std::function<T(void)>& F): source_device_key(0), source_parameter_hashes(), update_count(0), cache(), update_function(F){
            source_parameter_hashes.set_empty_key(0);
        }

        Result() = delete;

        template<typename T1, typename T2>
        friend bool operator==(const Result<T1>&, const Result<T2>&);

        friend Device;
    };

    template<typename T1, typename T2>
    bool deepCompare(const Result<T1>& A, const Result<T2>& B){
        if(A != B){
            return false;
        }
        return A.update_count == B.update_count;
    }

    template<typename T1, typename T2>
    bool operator==(const Result<T1>& A, const Result<T2>& B){
        if(!std::is_same_v<T1,T2>){
            return false;
        }
        if(A.source_device_key != B.source_device_key){
            return false;
        }
        if(A.source_parameter_hashes != B.source_parameter_hashes){
            return false;
        }
        if(A.update_function != B.update_function){
            return false;
        }
        return A.cache == B.cache;
    }
}
