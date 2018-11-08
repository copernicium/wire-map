#include "wiremap.hpp"

namespace wiremap{
    std::shared_ptr<google::dense_hash_map<detail::KeyType,Device,detail::Hasher,detail::KeyCompare>> WireMap::devices = nullptr;

	void WireMap::reset(){
		devices = std::make_shared<google::dense_hash_map<detail::KeyType,Device,detail::Hasher,detail::KeyCompare>>();
		devices->set_empty_key(0);
	}

	Device& WireMap::get(const detail::KeyType& KEY)noexcept{
		assert(devices != nullptr && devices->find(KEY) != devices->end());
		return (*devices)[KEY];
	}

	Device& WireMap::get(const std::string& KEY)noexcept{
		return get(hashstr(KEY));
	}

	bool WireMap::exists(const detail::KeyType& KEY)noexcept{
		if(devices == nullptr){
			return false;
		}
		return devices->find(KEY) != devices->end();
	}

	bool WireMap::exists(const std::string& KEY)noexcept{
		return exists(hashstr(KEY));
	}

	std::shared_ptr<google::dense_hash_map<detail::KeyType,Function,detail::Hasher,detail::KeyCompare>> Functions::functions = nullptr;

	Function& Functions::get(const detail::KeyType& KEY)noexcept{
		if(functions == nullptr){
			functions = std::make_shared<google::dense_hash_map<detail::KeyType,Function,detail::Hasher,detail::KeyCompare>>();
			functions->set_empty_key(0);
		}
		return (*functions)[KEY];
	}
}
