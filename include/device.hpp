#pragma once

#include <memory>
#include "device_bases.hpp"

namespace wiremap{
    struct Device{
    private:
        google::dense_hash_map<detail::KeyType,std::shared_ptr<detail::ParameterBase>,detail::Hasher,detail::KeyCompare> parameters;

        google::dense_hash_map<detail::KeyType,std::shared_ptr<const detail::ConstantBase>,detail::Hasher,detail::KeyCompare> constants;

        google::dense_hash_map<detail::KeyType,std::shared_ptr<detail::ResultBase>,detail::Hasher,detail::KeyCompare> results;

    public:
        const std::shared_ptr<detail::ParameterBase>& getParameter(const detail::KeyType& KEY)const noexcept{
			const auto& i = parameters.find(KEY);
			assert(i != parameters.end());
            return i->second;
        }

		template<typename RawKeyType, typename = std::enable_if_t<std::is_convertible_v<RawKeyType, std::string>>>
		const std::shared_ptr<detail::ParameterBase>& getParameter(const RawKeyType& KEY)const noexcept{
			return getParameter(hashstr(KEY));
		}

        const std::shared_ptr<const detail::ConstantBase>& getConstant(const detail::KeyType& KEY)const noexcept{
			const auto& i = constants.find(KEY);
			assert(i != constants.end());
            return i->second;
        }

		template<typename RawKeyType, typename = std::enable_if_t<std::is_convertible_v<RawKeyType, std::string>>>
        const std::shared_ptr<const detail::ConstantBase>& getConstant(const RawKeyType& KEY)const noexcept{
			return getConstant(hashstr(KEY));
		}

        const std::shared_ptr<detail::ResultBase>& getResult(const detail::KeyType& KEY)const noexcept{
			const auto& i = results.find(KEY);
			assert(i != results.end());
            return i->second;
        }

		template<typename RawKeyType, typename = std::enable_if_t<std::is_convertible_v<RawKeyType, std::string>>>
        const std::shared_ptr<detail::ResultBase>& getResult(const RawKeyType& KEY)const noexcept{
			return getResult(hashstr(KEY));
		}

		bool exists(const detail::KeyType& KEY)const{
			return parameters.find(KEY) != parameters.end() ||
				constants.find(KEY) != constants.end() ||
				results.find(KEY) != results.end();
		}

        Device()noexcept{
			results.set_empty_key(0);
			parameters.set_empty_key(0);
			constants.set_empty_key(0);
		}

		Device(const detail::KeyType&)noexcept: Device(){}

        template<typename First, typename... Members>
        Device(const detail::KeyType& DEVICE_KEY, const std::pair<detail::KeyType, First>& first_member, const Members&... members)noexcept: Device(DEVICE_KEY, members...){
            static_assert(std::is_base_of_v<detail::DeviceMemberBase,First>, "Constructing device from non-member type");

			assert(!exists(first_member.first));

			if constexpr(std::is_base_of_v<detail::ResultBase,First>){
                results[first_member.first] = std::make_shared<First>(first_member.second);
				results[first_member.first]->setSourceDeviceKey(DEVICE_KEY);
            } else if constexpr(std::is_base_of_v<detail::ParameterBase,First>){
                parameters[first_member.first] = std::make_shared<First>(first_member.second);
            } else if constexpr(std::is_base_of_v<detail::ConstantBase,First>){
                constants[first_member.first] = std::make_shared<First>(first_member.second);
            }
        }

		template<typename RawKeyType, typename = std::enable_if_t<std::is_convertible_v<RawKeyType, std::string>>, typename First, typename... Members>
        Device(const detail::KeyType& DEVICE_KEY, const std::pair<RawKeyType, First>& first_member, const Members&... members)noexcept: Device(DEVICE_KEY, std::make_pair(hashstr(first_member.first), first_member.second), members...){}

        template<typename... Members>
        Device(const std::string& DEVICE_KEY, const Members&... members)noexcept: Device(hashstr(DEVICE_KEY), members...){}
    };
}
