#pragma once

#include <memory>
#include "device_bases.hpp"

namespace wiremap{
    struct Device{
    private:
        std::shared_ptr<google::dense_hash_map<detail::KeyType,std::shared_ptr<detail::ParameterBase>,detail::Hasher,detail::KeyCompare>> parameters;

        std::shared_ptr<google::dense_hash_map<detail::KeyType,std::shared_ptr<detail::ConstantBase>,detail::Hasher,detail::KeyCompare>> constants;

        std::shared_ptr<google::dense_hash_map<detail::KeyType,std::shared_ptr<detail::ResultBase>,detail::Hasher,detail::KeyCompare>> results;

    public:
        const std::shared_ptr<const detail::ParameterBase> getParameter(const detail::KeyType& KEY)const noexcept{
            assert(parameters != nullptr);
			auto i = parameters->find(KEY);
			assert(i != parameters->end());
            return i->second;
        }

        const std::shared_ptr<const detail::ConstantBase> getConstant(const detail::KeyType& KEY)const noexcept{
            assert(constants != nullptr);
			auto i = constants->find(KEY);
			assert(i != constants->end());
            return i->second;
        }

        const std::shared_ptr<const detail::ResultBase> getResult(const detail::KeyType& KEY)const noexcept{
            assert(results != nullptr);
			auto i = results->find(KEY);
			assert(i != results->end());
            return i->second;
        }

		bool exists(const detail::KeyType& KEY)const{
			if(parameters != nullptr && parameters->find(KEY) != parameters->end()){
				return true;
			}
			if(constants != nullptr && constants->find(KEY) != constants->end()){
				return true;
			}
			if(results != nullptr && results->find(KEY) != results->end()){
				return true;
			}
			return false;
		}

        Device()noexcept{}
        Device(const detail::KeyType&)noexcept{}

        template<typename First, typename... Members>
        Device(const std::pair<detail::KeyType, First>& first_member, const Members&... members)noexcept: Device(members...){
            static_assert(std::is_base_of_v<detail::DeviceMemberBase,First>, "Constructing device from non-member type");
			assert(!exists(first_member.first));
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

        template<typename RawKeyType, typename First, typename... Members>
        Device(const std::pair<RawKeyType, First>& first_member, const Members&... members)noexcept: Device(std::make_pair(hashstr(first_member.first),first_member.second), members...){}

        template<typename... Members>
        Device(const detail::KeyType& DEVICE_KEY, const Members&... members)noexcept: Device(members...){
            if(results != nullptr){
                for(std::pair<detail::KeyType, std::shared_ptr<detail::ResultBase>> result: *results){
                    result.second->setSourceDeviceKey(DEVICE_KEY);
                }
            }
        }

        template<typename... Members>
        Device(const std::string& DEVICE_KEY, const Members&... members)noexcept: Device(hashstr(DEVICE_KEY), members...){}
    };
}
