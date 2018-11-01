#include "object.hpp"

namespace wiremap{
	struct ToString{
		template<typename T, typename = std::enable_if_t<detail::is_wiremap_primitive_v<T>>>
		std::string operator()(const Type&, const T& a)const noexcept{
			return std::to_string(a.require()); // TODO handle requiring
		}
	};

	ToString toString;

	struct Sum{
		template<typename T, typename = std::enable_if_t<detail::is_wiremap_primitive_v<T>>>
		Object operator()(const Type& TYPE, const T& a, const T& b)const noexcept{
			assert(TYPE != Type::CONTAINER);
			return Object::primitive(TYPE, a + b);
		}

		template<typename T, typename R, typename = std::enable_if_t<detail::is_wiremap_primitive_v<T>>>
		Object operator()(const Type& TYPE, const T& a, const R& b)const noexcept{
			return operator()(TYPE, a, T(b));
		}
	};

	Sum sum;
}
