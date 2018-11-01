#include "object.hpp"

namespace wiremap{
	Type toType(const std::string& IN){
		if(IN == "Real"){
			return Type::REAL;
		} else if(IN == "Integer"){
			return Type::INTEGER;
		}
		assert(0);
	}
}
