#pragma once

#include <memory>
#include "device_bases.hpp"
#include "map.hpp"

namespace wiremap{

    struct Device{
    private:
        std::shared_ptr<google::dense_hash_map<KeyType,std::shared_ptr<ResultBase>,Hasher,KeyCompare>> results;

    public:
        std::shared_ptr<ResultBase>& getResult(std::size_t r_hash)const noexcept{
            return (*results)[r_hash];
        }

        Device()noexcept:results(std::make_shared<google::dense_hash_map<KeyType,std::shared_ptr<ResultBase>,Hasher,KeyCompare>>()){
            results->set_empty_key(0);
        }

    };
}
