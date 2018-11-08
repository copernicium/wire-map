#include "device.hpp"

namespace wiremap{
	const std::shared_ptr<Parameter>& Device::getParameter(const detail::KeyType& KEY)const noexcept{
		const auto& i = parameters.find(KEY);
		assert(i != parameters.end());
		return i->second;
	}

	const std::shared_ptr<const detail::ConstantBase>& Device::getConstant(const detail::KeyType& KEY)const noexcept{
		const auto& i = constants.find(KEY);
		assert(i != constants.end());
		return i->second;
	}

	const std::shared_ptr<Result>& Device::getResult(const detail::KeyType& KEY)const noexcept{
		const auto& i = results.find(KEY);
		assert(i != results.end());
		return i->second;
	}

	bool Device::exists(const detail::KeyType& KEY)const{
		return parameters.find(KEY) != parameters.end() ||
			constants.find(KEY) != constants.end() ||
			results.find(KEY) != results.end();
	}

	Device::Device()noexcept{
		results.set_empty_key(0);
		parameters.set_empty_key(0);
		constants.set_empty_key(0);
	}

	Device::Device(const detail::KeyType& DEVICE_KEY)noexcept: Device(){
		device_key = DEVICE_KEY;
	}
}
