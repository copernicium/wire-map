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
        const std::shared_ptr<const detail::ParameterBase> getParameter(const detail::KeyType& P_KEY)const noexcept{
            assert(parameters != nullptr && (*parameters)[P_KEY] != nullptr);
            return (*parameters)[P_KEY];
        }

        const std::shared_ptr<const detail::ConstantBase> getConstant(const detail::KeyType& C_KEY)const noexcept{
            assert(constants != nullptr && (*constants)[C_KEY] != nullptr);
            return (*constants)[C_KEY];
        }

        const std::shared_ptr<const detail::ResultBase> getResult(const detail::KeyType& R_KEY)const noexcept{
            assert(results != nullptr && (*results)[R_KEY] != nullptr);
            return (*results)[R_KEY];
        }

        Device()noexcept{}
        Device(const detail::KeyType&)noexcept{}

        template<typename First, typename... Members>
        Device(const std::pair<detail::KeyType, First>& first_member, Members... members)noexcept: Device(members...){
            static_assert(std::is_base_of_v<detail::DeviceMemberBase,First>, "Constructing device from non-member type");
            if constexpr(std::is_base_of_v<detail::ResultBase,First>){
                if(results == nullptr){
                    results = std::make_shared<google::dense_hash_map<detail::KeyType,std::shared_ptr<detail::ResultBase>,detail::Hasher,detail::KeyCompare>>();
                    results->set_empty_key(0);
                }
                (*results)[first_member.first] = std::make_shared<First>(first_member.second);
            } else if constexpr(std::is_base_of_v<detail::ParameterBase,First>){
                if(parameters == nullptr){
                    parameters = std::make_shared<google::dense_hash_map<detail::KeyType,std::shared_ptr<detail::ParameterBase>,detail::Hasher,detail::KeyCompare>>();
                    parameters->set_empty_key(0);
                }
                (*parameters)[first_member.first] = std::make_shared<First>(first_member.second);
            } else if constexpr(std::is_base_of_v<detail::ConstantBase,First>){
                if(constants == nullptr){
                    constants = std::make_shared<google::dense_hash_map<detail::KeyType,std::shared_ptr<detail::ConstantBase>,detail::Hasher,detail::KeyCompare>>();
                    constants->set_empty_key(0);
                }
                (*constants)[first_member.first] = std::make_shared<First>(first_member.second);
            }
        }

        template<typename... Members>
        Device(const detail::KeyType& DEVICE_KEY, Members... members)noexcept: Device(members...){
            if(results != nullptr){
                for(std::pair<detail::KeyType, std::shared_ptr<detail::ResultBase>> result: *results){
                    result.second->setSourceDeviceKey(DEVICE_KEY);
                }
            }
        }
    };
}
