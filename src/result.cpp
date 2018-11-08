#include "result.hpp"

namespace wiremap{
	void Result::setSourceDeviceKey(const detail::KeyType& D_KEY){
		source_device_key = D_KEY;
	}

	const Object& Result::get(){
		if(!cache.has_value()){
			cache = update_function();
		}
		return cache.value();
	}

	Result::Result(const std::function<Object(void)>& F): source_device_key(0), source_parameter_hashes(), cache(), update_function(F){
		source_parameter_hashes.set_empty_key(0);
	}

    bool operator==(const Result& A, const Result& B){
        if(A.source_device_key != B.source_device_key){
            return false;
        }
        if(A.source_parameter_hashes != B.source_parameter_hashes){
            return false;
        }
        // if(A.update_function != B.update_function){
        //     return false;
        // }
        return A.cache == B.cache;
    }

	bool operator!=(const Result& A, const Result& B){
		return !(A == B);
	}

	bool deepCompare(const Result& A, const Result& B){
        if(A != B){
            return false;
        }
		return true; // return A.update_count == B.update_count;
    }

}
