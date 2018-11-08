#include "object.hpp"

namespace wiremap{
	struct Assign{
        template<typename T, typename R, typename = std::enable_if_t<detail::is_wiremap_primitive_v<T>>>
		void operator()(T& a, const R& b)const noexcept{
			a = b;
		}
	};

	const Assign assign;

	struct ToString{
		template<typename T, typename = std::enable_if_t<detail::is_wiremap_primitive_v<T>>>
		std::string operator()(const T& a)const noexcept{
			return std::to_string(a.require()); // TODO handle requiring
		}
	};

	const ToString to_string;

	struct Sum{
		template<typename T, typename = std::enable_if_t<detail::is_wiremap_primitive_v<T>>>
		Object operator()(const T& a, const T& b)const noexcept{
			return Object::primitive(a + b);
		}

		template<typename T, typename R, typename = std::enable_if_t<detail::is_wiremap_primitive_v<T>>>
		Object operator()(const T& a, const R& b)const noexcept{
			return operator()(a, T(b));
		}
	};

	const Sum sum;

	struct CompareEqual{
		template<typename T, typename = std::enable_if_t<detail::is_wiremap_primitive_v<T>>>
		bool operator()(const T& a, const T& b)const{
			return a == b;
		}
	};

	const CompareEqual compare_equal;
}
