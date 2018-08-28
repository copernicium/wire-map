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
        const std::shared_ptr<const detail::ParameterBase> getParameter(std::size_t p_hash)const noexcept{
            assert(parameters != nullptr && (*parameters)[p_hash] != nullptr);
            return (*parameters)[p_hash];
        }

        const std::shared_ptr<const detail::ConstantBase> getConstant(std::size_t c_hash)const noexcept{
            assert(constants != nullptr && (*constants)[c_hash] != nullptr);
            return (*constants)[c_hash];
        }

        const std::shared_ptr<const detail::ResultBase> getResult(std::size_t r_hash)const noexcept{
            assert(results != nullptr && (*results)[r_hash] != nullptr);
            return (*results)[r_hash];
        }

        Device()noexcept{}

        template<typename First, typename... Members>
        Device(const std::pair<detail::KeyType, std::shared_ptr<First>>& first_member, Members... members)noexcept: Device(members...){
            static_assert(std::is_base_of_v<detail::DeviceMemberBase,First>, "Constructing device from non-member type");
            if constexpr(std::is_base_of_v<detail::ResultBase,First>){
                if(results == nullptr){
                    results = std::make_shared<google::dense_hash_map<detail::KeyType,std::shared_ptr<detail::ResultBase>,detail::Hasher,detail::KeyCompare>>();
                    results->set_empty_key(0);
                }
                (*results)[first_member.first] = first_member.second;
            } else if constexpr(std::is_base_of_v<detail::ParameterBase,First>){
                if(parameters == nullptr){
                    parameters = std::make_shared<google::dense_hash_map<detail::KeyType,std::shared_ptr<detail::ParameterBase>,detail::Hasher,detail::KeyCompare>>();
                    parameters->set_empty_key(0);
                }
                (*parameters)[first_member.first] = first_member.second;
            } else if constexpr(std::is_base_of_v<detail::ConstantBase,First>){
                if(constants == nullptr){
                    constants = std::make_shared<google::dense_hash_map<detail::KeyType,std::shared_ptr<detail::ConstantBase>,detail::Hasher,detail::KeyCompare>>();
                    constants->set_empty_key(0);
                }
                (*constants)[first_member.first] = first_member.second;
            }
        }
    };
}
