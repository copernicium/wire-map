#pragma once

#include <memory>
#include "device_bases.hpp"
#include "function.hpp"
#include "map.hpp"
#include "object.hpp"
#include "wiremap.hpp"

namespace wiremap{
    template<typename T>
    struct Result: public detail::ResultBase{
        static_assert(detail::is_wiremap_object_v<T>,"Constant built from type not derived from detail::ObjectBase");
    protected:
        detail::KeyType source_device_hash;
        std::shared_ptr<google::dense_hash_map<detail::KeyType,detail::KeyType,detail::Hasher,detail::KeyCompare>> source_parameter_hashes;
        unsigned update_count;
        std::shared_ptr<T> cache;
        Function update_function;

    public:
        const std::shared_ptr<T>& get(){
            bool update = false;
            for(const std::pair<detail::KeyType, detail::KeyType>& source_parameter: *source_parameter_hashes){
                //TODO check if results parameters point to have been updated
            }
            if(update){
                update_count++;
                //update_function
                // return WireMap::get(source_device_hash).getParameter(source_parameter_hashes);
            }
            return cache;
        }

        Result(const detail::KeyType& d_hash, const T& v): source_device_hash(d_hash), source_parameter_hashes(std::make_shared<google::dense_hash_map<detail::KeyType,detail::KeyType,detail::Hasher,detail::KeyCompare>>()), update_count(0), cache(std::make_shared<T>(v)){
            source_parameter_hashes->set_empty_key(0);
        } //TODO no result constructor should take a T--use update instead

        Result() = delete;

        template<typename T1, typename T2>
        friend bool operator==(const Result<T1>&, const Result<T2>&);
    };

    template<typename T1, typename T2>
    bool deepCompare(const Result<T1>& A, const Result<T2>& B){
        if(A == B){
            return true;
        }
        return A.update_count == B.update_count;
    }

    template<typename T1, typename T2>
    bool operator==(const Result<T1>& A, const Result<T2>& B){
        if(!std::is_same_v<T1,T2>){
            return false;
        }
        if((A.cache == nullptr) != (B.cache == nullptr)){
            return false;
        }
        if(A.cache != nullptr){
            return (*A.cache) == (*B.cache);
        }
        return true;
    }
}
