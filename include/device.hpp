#pragma once

#include <memory>
#include "device_bases.hpp"
#include "map.hpp"

namespace wiremap{

    struct Device{
    private:
        std::shared_ptr<google::dense_hash_map<detail::KeyType,std::shared_ptr<detail::ParameterBase>,detail::Hasher,detail::KeyCompare>> parameters;

        std::shared_ptr<google::dense_hash_map<detail::KeyType,std::shared_ptr<detail::ConstantBase>,detail::Hasher,detail::KeyCompare>> constants;

        std::shared_ptr<google::dense_hash_map<detail::KeyType,std::shared_ptr<detail::ResultBase>,detail::Hasher,detail::KeyCompare>> results;

    public:
        std::shared_ptr<detail::ResultBase>& getResult(std::size_t r_hash)noexcept{ //TODO should return const once constructor is capable of defining results
            return (*results)[r_hash];
        }

        Device()noexcept: parameters(std::make_shared<google::dense_hash_map<detail::KeyType,std::shared_ptr<detail::ParameterBase>,detail::Hasher,detail::KeyCompare>>()), constants(std::make_shared<google::dense_hash_map<detail::KeyType,std::shared_ptr<detail::ConstantBase>,detail::Hasher,detail::KeyCompare>>()), results(std::make_shared<google::dense_hash_map<detail::KeyType,std::shared_ptr<detail::ResultBase>,detail::Hasher,detail::KeyCompare>>()){
            parameters->set_empty_key(0);
            constants->set_empty_key(0);
            results->set_empty_key(0);
        }

    };
}
