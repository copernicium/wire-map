#pragma once

#include "map_util.hpp"
#include "object.hpp"

namespace wiremap{
	struct Parameter; // TODO necessary?

	struct Result;

	struct Device{
    private:
		detail::KeyType device_key;

        google::dense_hash_map<detail::KeyType,std::shared_ptr<Parameter>,detail::Hasher,detail::KeyCompare> parameters;

        google::dense_hash_map<detail::KeyType,std::shared_ptr<const Object>,detail::Hasher,detail::KeyCompare> constants;

        google::dense_hash_map<detail::KeyType,std::shared_ptr<Result>,detail::Hasher,detail::KeyCompare> results;

    public:
        const std::shared_ptr<Parameter>& getParameter(const detail::KeyType&)const noexcept;

		const std::shared_ptr<Parameter>& getParameter(const std::string& KEY)const noexcept{
			return getParameter(hasher(KEY));
		}

        const std::shared_ptr<const Object>& getConstant(const detail::KeyType&)const noexcept;

        const std::shared_ptr<const Object>& getConstant(const std::string& KEY)const noexcept{
			return getConstant(hasher(KEY));
		}

        const std::shared_ptr<Result>& getResult(const detail::KeyType&)const noexcept;

        const std::shared_ptr<Result>& getResult(const std::string& KEY)const noexcept{
			return getResult(hasher(KEY));
		}

		bool exists(const detail::KeyType&)const;

        template<typename Member, typename = std::enable_if_t<std::is_same_v<Object, Member> || std::is_same_v<Parameter, Member> || std::is_same_v<Result, Member>>>
        void add(const std::pair<detail::KeyType, Member>& MEMBER)noexcept{
			assert(!exists(MEMBER.first));

			if constexpr(std::is_same_v<Result,Member>){
                results[MEMBER.first] = std::make_shared<Member>(MEMBER.second);
				results[MEMBER.first]->setSourceDeviceKey(device_key);
            } else if constexpr(std::is_same_v<Parameter,Member>){
                parameters[MEMBER.first] = std::make_shared<Member>(MEMBER.second);
            } else if constexpr(std::is_same_v<Object, Member>){
                constants[MEMBER.first] = std::make_shared<Member>(MEMBER.second);
            }
        }

        Device()noexcept;

		Device(const detail::KeyType&)noexcept;

        template<typename First, typename... Members>
        Device(const detail::KeyType& DEVICE_KEY, const std::pair<detail::KeyType, First>& first_member, const Members&... members)noexcept: Device(DEVICE_KEY, members...){
			static_assert(std::is_same_v<Object, First> || std::is_same_v<Parameter, First> || std::is_same_v<Result, First>, "Constructing device from non-member type");

			assert(!exists(first_member.first));

			if constexpr(std::is_same_v<Result,First>){
                results[first_member.first] = std::make_shared<First>(first_member.second);
				results[first_member.first]->setSourceDeviceKey(DEVICE_KEY);
            } else if constexpr(std::is_same_v<Parameter,First>){
                parameters[first_member.first] = std::make_shared<First>(first_member.second);
            } else if constexpr(std::is_same_v<Object,First>){
                constants[first_member.first] = std::make_shared<First>(first_member.second);
			}
        }

		template<typename First, typename... Members>
        Device(const detail::KeyType& DEVICE_KEY, const std::pair<std::string, First>& first_member, const Members&... members)noexcept: Device(DEVICE_KEY, std::make_pair(hasher(first_member.first), first_member.second), members...){}

        template<typename... Members>
        Device(const std::string& DEVICE_KEY, const Members&... members)noexcept: Device(hasher(DEVICE_KEY), members...){}
    };
}
