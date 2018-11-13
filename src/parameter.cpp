#include "parameter.hpp"
#include "wiremap.hpp"

namespace wiremap{
	Parameter::Parameter(const detail::KeyType& device_key, const detail::KeyType& result_key)noexcept: source_device_key(device_key), source_result_key(result_key), source(nullptr){}

	Parameter::Parameter(const std::string& d_src, const std::string& r_src)noexcept: Parameter(hasher(d_src),hasher(r_src)){}

	const Object& Parameter::get()noexcept{
		if(source == nullptr){
			source = WireMap::get(source_device_key).getResult(source_result_key);
		}
		return source->get();
	}
}
