#pragma once

#include "primitive.hpp"
#include "constant.hpp"

#include <memory>
#include <tuple>
#include <variant>
#include <vector>

namespace wiremap{
	// Definition of primitive types
    template<typename T>
    using Integral = detail::Primitive<T, 0, attributes::Integral<T>>;

    using Bit = Integral<bool>;
    using Char = Integral<char>;
    using Byte = Integral<uint8_t>;
    using Word = Integral<uint16_t>;
    using DWord = Integral<uint32_t>;
    using QWord = Integral<uint64_t>;
    using Integer = Integral<long>;

    using Bool = detail::Primitive<bool, false>;
    using Real = detail::Primitive<double, 0>;

	// Feature to be added in C++20
	template<typename T>
	struct remove_cvref{
		using type = std::remove_cv_t<std::remove_reference_t<T>>;
	};

	template<typename T>
	using remove_cvref_t = typename remove_cvref<T>::type;

    // Meta type helpers

	enum class Type{ // Order must correspond to that in TypeInterface
		UNKNOWN,
		BIT,
		CHAR,
		BYTE,
		WORD,
		DWORD,
		QWORD,
		INTEGER,
		BOOL,
		REAL,
		CONTAINER
	};

	namespace detail{
		template<typename... Types>
		struct TypeInterfaceImpl{
			template<Type I>
			using element = std::tuple_element_t<static_cast<std::size_t>(I), std::tuple<Types...>>;

			using variant = std::variant<Types...>;

			template<typename T>
			static variant create(const Type& TYPE, const T& VALUE)noexcept{
				switch(TYPE){
				case Type::BIT:
					return (element<Type::BIT>)VALUE;
				case Type::CHAR:
					return (element<Type::CHAR>)VALUE;
				case Type::BYTE:
					return (element<Type::BYTE>)VALUE;
				case Type::WORD:
					return (element<Type::WORD>)VALUE;
				case Type::DWORD:
					return (element<Type::DWORD>)VALUE;
				case Type::QWORD:
					return (element<Type::QWORD>)VALUE;
				case Type::INTEGER:
					return (element<Type::INTEGER>)VALUE;
				case Type::BOOL:
					return (element<Type::BOOL>)VALUE;
				case Type::REAL:
					return (element<Type::REAL>)VALUE;
				case Type::CONTAINER:
					return (element<Type::CONTAINER>)VALUE;
				case Type::UNKNOWN:
					assert(0);; // Undefined
				default:
					NYI
				}
			}

			static variant create(const Type& TYPE)noexcept{
				switch(TYPE){
				case Type::BIT:
					return element<Type::BIT>();
				case Type::CHAR:
					return element<Type::CHAR>();
				case Type::BYTE:
					return element<Type::BYTE>();
				case Type::WORD:
					return element<Type::WORD>();
				case Type::DWORD:
					return element<Type::DWORD>();
				case Type::QWORD:
					return element<Type::QWORD>();
				case Type::INTEGER:
					return element<Type::INTEGER>();
				case Type::BOOL:
					return element<Type::BOOL>();
				case Type::REAL:
					return element<Type::REAL>();
				case Type::CONTAINER:
					return element<Type::CONTAINER>();
				case Type::UNKNOWN:
					assert(0); // Undefined
				default:
					NYI
				}
			}

			template<std::size_t I, bool F>
			struct index_base{
				static constexpr std::size_t value = I;
				static constexpr bool found = F;
			};

			template<typename...>
			struct index;

			template<typename Target, typename Miss>
			struct index<Target, Miss>: index_base<0, false>{};

			template<typename Target, typename... Remaining>
			struct index<Target, Target, Remaining...>: index_base<0, true>{};

			template<typename Target, typename Miss, typename... Remaining>
			struct index<Target, Miss, Remaining...>: index_base<1 + index<Target ,Remaining...>::value, index<Target, Remaining...>::found>{};

		public:
			template<typename T>
			static Type deduce(const T&)noexcept{
				return index<T, Types...>::found ? static_cast<Type>(index<T, Types...>::value) : Type::UNKNOWN;
			}
		};
	}

	struct Object;

	using TypeInterface = detail::TypeInterfaceImpl< // Order must correspond to Type enum class
		std::monostate,
		Bit,
		Char,
		Byte,
		Word,
		DWord,
		QWord,
		Integer,
		Bool,
		Real,
		std::vector<std::shared_ptr<Object>> // TODO: use unique_ptr?
	>;

	// The class that will actually be used during operation; can contain primitives, lists, and collections; types determined during runtime
	struct Object{
	private:
		Type type;

		TypeInterface::variant value;

		// Constructors

		Object() = delete;

		Object(const Type&)noexcept;

		template<typename T>
		Object(const Type& TYPE, const T& VALUE)noexcept: type(TYPE), value(TypeInterface::create(type, VALUE)){}

		Object(const Object&, const std::size_t&)noexcept;

		Object(const std::vector<Object>& TYPES)noexcept;

	public:
		~Object()noexcept = default;

		Object(Object&&)noexcept = default;

		Object(const Object&)noexcept;

		Object& operator=(const Object&)noexcept;

		Object& operator=(Object&&)noexcept;

		//Explicit constructors

		static Object primitive(const Type&)noexcept;

		template<typename T>
		static Object primitive(const T& VALUE)noexcept{
			Type type = TypeInterface::deduce(VALUE);
			assert(type != Type::CONTAINER);
			return Object(type, VALUE);
		}

		template<typename T>
		static Object primitive(const Type& TYPE, const T& VALUE)noexcept{
			assert(TYPE != Type::CONTAINER);
			return Object(TYPE, VALUE);
		}

		static Object list(const Object&, const std::size_t&)noexcept;

		static Object collection(const std::vector<Object>&)noexcept;

		std::shared_ptr<Object> clone()const noexcept;

		template<typename... Args>
		std::shared_ptr<Object> create(const Args&... ARGS)noexcept{
			return std::make_shared<Object>(Object(ARGS...));
		}

		// Accessors

		const Type& getType()const noexcept;

		Object& at(const std::size_t&);

		const Object& at(const std::size_t&)const;

		std::size_t size()const noexcept;

		// Visit functions

		template<typename F, typename TObject1, typename TObject2, typename... Args, typename = std::enable_if_t<std::is_same_v<remove_cvref_t<TObject1>, Object> && std::is_same_v<remove_cvref_t<TObject2>, Object>>>
		static auto visit(const F& f, TObject1& a, TObject2& b, const Args&... args){
			assert(a.getType() == b.getType());

			switch(a.getType()){
			case Type::BIT:
				return f(std::get<TypeInterface::element<Type::BIT>>(a.value), std::get<TypeInterface::element<Type::BIT>>(b.value), args...);
			case Type::CHAR:
				return f(std::get<TypeInterface::element<Type::CHAR>>(a.value), std::get<TypeInterface::element<Type::CHAR>>(b.value), args...);
			case Type::BYTE:
				return f(std::get<TypeInterface::element<Type::BYTE>>(a.value), std::get<TypeInterface::element<Type::BYTE>>(b.value), args...);
			case Type::WORD:
				return f(std::get<TypeInterface::element<Type::WORD>>(a.value), std::get<TypeInterface::element<Type::WORD>>(b.value), args...);
			case Type::DWORD:
				return f(std::get<TypeInterface::element<Type::DWORD>>(a.value), std::get<TypeInterface::element<Type::DWORD>>(b.value), args...);
			case Type::QWORD:
				return f(std::get<TypeInterface::element<Type::QWORD>>(a.value), std::get<TypeInterface::element<Type::QWORD>>(b.value), args...);
			case Type::INTEGER:
				return f(std::get<TypeInterface::element<Type::INTEGER>>(a.value), std::get<TypeInterface::element<Type::INTEGER>>(b.value), args...);
			case Type::BOOL:
				return f(std::get<TypeInterface::element<Type::BOOL>>(a.value), std::get<TypeInterface::element<Type::BOOL>>(b.value), args...);
			case Type::REAL:
				return f(std::get<TypeInterface::element<Type::REAL>>(a.value), std::get<TypeInterface::element<Type::REAL>>(b.value), args...);
			case Type::CONTAINER:
				[[fallthrough]]; // Undefined
			case Type::UNKNOWN:
				assert(0); // Undefined
			default:
				NYI
			}
		}

		template<typename F, typename TObject, typename... Args, typename = std::enable_if_t<std::is_same_v<remove_cvref_t<TObject>, Object>>>
		static auto visit(const F& f, TObject& a, const Args&... args){
			switch(a.getType()){
			case Type::BIT:
				return f(std::get<TypeInterface::element<Type::BIT>>(a.value), args...);
			case Type::CHAR:
				return f(std::get<TypeInterface::element<Type::CHAR>>(a.value), args...);
			case Type::BYTE:
				return f(std::get<TypeInterface::element<Type::BYTE>>(a.value), args...);
			case Type::WORD:
				return f(std::get<TypeInterface::element<Type::WORD>>(a.value), args...);
			case Type::DWORD:
				return f(std::get<TypeInterface::element<Type::DWORD>>(a.value), args...);
			case Type::QWORD:
				return f(std::get<TypeInterface::element<Type::QWORD>>(a.value), args...);
			case Type::INTEGER:
				return f(std::get<TypeInterface::element<Type::INTEGER>>(a.value), args...);
			case Type::BOOL:
				return f(std::get<TypeInterface::element<Type::BOOL>>(a.value), args...);
			case Type::REAL:
				return f(std::get<TypeInterface::element<Type::REAL>>(a.value), args...);
			case Type::CONTAINER:
				[[fallthrough]]; // Undefined
			case Type::UNKNOWN:
				assert(0); // Undefined
			default:
				NYI
			}
		}

		bool operator==(const Object&)const;
	};
}
