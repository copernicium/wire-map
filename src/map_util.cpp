#include "map_util.hpp"

namespace wiremap{
	std::size_t hasher(const std::string& A){
		return std::hash<std::string>()(A);
	}
}
