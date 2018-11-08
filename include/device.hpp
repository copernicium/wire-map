#pragma once

#include <memory>
#include "device_bases.hpp"

namespace wiremap{
	struct Parameter; // TODO necessary?

	struct Result;

	struct Device{
    private:
		detail::KeyType device_key;

        google::dense_hash_map<detail::KeyType,std::shared_ptr<Parameter>,detail::Hasher,detail::KeyCompare> parameters;

        google::dense_hash_map<detail::KeyType,std::shared_ptr<const detail::ConstantBase>,detail::Hasher,detail::KeyCompare> constants;

        google::dense_hash_map<detail::KeyType,std::shared_ptr<Result>,detail::Hasher,detail::KeyCompare> results;

    public:
        const std::shared_ptr<Parameter>& getParameter(const detail::KeyType&)const noexcept;

		template<typename RawKeyType, typename = std::enable_if_t<std::is_convertible_v<RawKeyType, std::string>>>
		const std::shared_ptr<Parameter>& getParameter(const RawKeyType& KEY)const noexcept{
			return getParameter(hashstr(KEY));
		}

        const std::shared_ptr<const detail::ConstantBase>& getConstant(const detail::KeyType&)const noexcept;

		template<typename RawKeyType, typename = std::enable_if_t<std::is_convertible_v<RawKeyType, std::string>>>
        const std::shared_ptr<const detail::ConstantBase>& getConstant(const RawKeyType& KEY)const noexcept{
			return getConstant(hashstr(KEY));
		}

        const std::shared_ptr<Result>& getResult(const detail::KeyType&)const noexcept;

		template<typename RawKeyType, typename = std::enable_if_t<std::is_convertible_v<RawKeyType, std::string>>>
        const std::shared_ptr<Result>& getResult(const RawKeyType& KEY)const noexcept{
			return getResult(hashstr(KEY));
		}

		bool exists(const detail::KeyType&)const;

        template<typename Member, typename = std::enable_if_t<std::is_base_of_v<detail::DeviceMemberBase, Member>>>
        void add(const std::pair<detail::KeyType, Member>& MEMBER)noexcept{
			assert(!exists(MEMBER.first));

			if constexpr(std::is_same_v<Result,Member>){
                results[MEMBER.first] = std::make_shared<Member>(MEMBER.second);
				results[MEMBER.first]->setSourceDeviceKey(device_key);
            } else if constexpr(std::is_same_v<Parameter,Member>){
                parameters[MEMBER.first] = std::make_shared<Member>(MEMBER.second);
            } else if constexpr(std::is_base_of_v<detail::ConstantBase,Member>){
                constants[MEMBER.first] = std::make_shared<Member>(MEMBER.second);
            }
        }

        Device()noexcept;

		Device(const detail::KeyType&)noexcept;

        template<typename First, typename... Members>
        Device(const detail::KeyType& DEVICE_KEY, const std::pair<detail::KeyType, First>& first_member, const Members&... members)noexcept: Device(DEVICE_KEY, members...){
            static_assert(std::is_base_of_v<detail::DeviceMemberBase,First>, "Constructing device from non-member type");

			assert(!exists(first_member.first));

			if constexpr(std::is_same_v<Result,First>){
                results[first_member.first] = std::make_shared<First>(first_member.second);
				results[first_member.first]->setSourceDeviceKey(DEVICE_KEY);
            } else if constexpr(std::is_same_v<Parameter,First>){
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
