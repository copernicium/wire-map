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

	Type toType(const std::string&);

	namespace detail{
		template<typename... Types>
		struct TypeInterfaceImpl{
			template<Type I>
			using element = std::tuple_element_t<static_cast<std::size_t>(I), std::tuple<Types...>>;

			using variant = std::variant<Types...>;

			template<typename T>
			static void assign(const Type& TYPE, variant& v, const T& VALUE){
				switch(TYPE){
				case Type::BIT:
					v = (element<Type::BIT>)VALUE;
					return;;
				case Type::CHAR:
					v = (element<Type::CHAR>)VALUE;
					return;;
				case Type::BYTE:
					v = (element<Type::BYTE>)VALUE;
					return;;
				case Type::WORD:
					v = (element<Type::WORD>)VALUE;
					return;;
				case Type::DWORD:
					v = (element<Type::DWORD>)VALUE;
					return;;
				case Type::QWORD:
					v = (element<Type::QWORD>)VALUE;
					return;;
				case Type::INTEGER:
					v = (element<Type::INTEGER>)VALUE;
					return;;
				case Type::BOOL:
					v = (element<Type::BOOL>)VALUE;
					return;;
				case Type::REAL:
					v = (element<Type::REAL>)VALUE;
					return;
				case Type::CONTAINER:
					v = (element<Type::CONTAINER>)VALUE;
					return;
				case Type::UNKNOWN:
					[[fallthrough]]; // Undefined
				default:
					assert(0);
				}
			}

			static void reset(const Type& TYPE, variant& v){
				switch(TYPE){
				case Type::BIT:
					[[fallthrough]];
				case Type::CHAR:
					[[fallthrough]];
				case Type::BYTE:
					[[fallthrough]];
				case Type::WORD:
					[[fallthrough]];
				case Type::DWORD:
					[[fallthrough]];
				case Type::QWORD:
					[[fallthrough]];
				case Type::INTEGER:
					[[fallthrough]];
				case Type::BOOL:
					[[fallthrough]];
				case Type::REAL:
					assign(TYPE, v, 0);
					return;
				case Type::CONTAINER:
					v = element<Type::CONTAINER>();
					return;
				case Type::UNKNOWN:
					[[fallthrough]]; // Undefined
				default:
					assert(0);
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
			static Type deduce(const T&){
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
		std::vector<std::shared_ptr<Object>>
	>;

    // Visitor (declared here to use in Object class)

	struct Assign{
        template<typename T, typename R, typename = std::enable_if_t<detail::is_wiremap_primitive_v<T>>>
		void operator()(const Type&, T& a, const R& b)const noexcept{
			a = b;
		}
	};

	Assign assign;

	// The class that will actually be used during operation; can contain primitives, lists, and collections; types determined during runtime
	struct Object{
	private:
		Type type;

		TypeInterface::variant value;

		// Constructors

		Object() = delete;

		Object(const Type& TYPE)noexcept: type(TYPE){
			assert(type != Type::UNKNOWN);
			TypeInterface::reset(type, value);
		}

		template<typename T>
		Object(const Type& TYPE, const T& VALUE)noexcept: Object(TYPE){
			TypeInterface::assign(type, value, VALUE);
		}

		Object(const Object& TYPE, const std::size_t& SIZE)noexcept: Object(Type::CONTAINER){
			std::get<TypeInterface::element<Type::CONTAINER>>(value).reserve(SIZE);
			for(unsigned i = 0; i < SIZE; i++){
				std::get<TypeInterface::element<Type::CONTAINER>>(value).push_back(TYPE.clone());
			}
		}

		Object(const std::vector<Object>& TYPES)noexcept: Object(Type::CONTAINER){
			std::get<TypeInterface::element<Type::CONTAINER>>(value).reserve(TYPES.size());
			for(unsigned i = 0; i < TYPES.size(); i++){
				std::get<TypeInterface::element<Type::CONTAINER>>(value).push_back(TYPES[i].clone());
			}
		}

	public:
		~Object() = default;

		Object(Object&&) = default;

		Object(const Object& OTHER)noexcept: Object(OTHER.type){
			if(type == Type::CONTAINER){
				std::get<TypeInterface::element<Type::CONTAINER>>(value).reserve(OTHER.size());
				for(unsigned i = 0; i < OTHER.size(); i++){
					std::get<TypeInterface::element<Type::CONTAINER>>(value).push_back(OTHER.at(i).clone());
				}
			}
		}

		//Explicit constructors

		static Object primitive(const Type& TYPE)noexcept{
			assert(TYPE != Type::CONTAINER);
			return Object(TYPE);
		}

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

		static Object list(const Object& TYPE, const std::size_t& SIZE)noexcept{
			return Object(TYPE, SIZE);
		}

		static Object collection(const std::vector<Object>& TYPES)noexcept{
			return Object(TYPES);
		}

		std::shared_ptr<Object> clone()const noexcept{
			return std::make_shared<Object>(*this);
		}

		template<typename... Args>
		static std::shared_ptr<Object> create(const Args&... ARGS)noexcept{
			return std::make_shared<Object>(Object(ARGS...));
		}

		// Accessors

		const Type& getType()const noexcept{
			return type;
		}

		Object& at(const std::size_t& I){
			assert(type == Type::CONTAINER);
			return *(std::get<TypeInterface::element<Type::CONTAINER>>(value)).at(I);
		}

		const Object& at(const std::size_t& I)const{
			assert(type == Type::CONTAINER);
			return *(std::get<TypeInterface::element<Type::CONTAINER>>(value)).at(I);
		}

		std::size_t size()const noexcept{
			assert(type == Type::CONTAINER);
			return std::get<TypeInterface::element<Type::CONTAINER>>(value).size();
		}

		// Visit functions

		template<typename F, typename TObject1, typename TObject2, typename... Args, typename = std::enable_if_t<std::is_same_v<remove_cvref_t<TObject1>, Object> && std::is_same_v<remove_cvref_t<TObject2>, Object>>>
		static auto visit(const F& f, TObject1& a, TObject2& b, const Args&... args){
			assert(a.getType() == b.getType());

			switch(a.getType()){
			case Type::BIT:
				return f(a.getType(), std::get<TypeInterface::element<Type::BIT>>(a.value), std::get<TypeInterface::element<Type::BIT>>(b.value), args...);
			case Type::CHAR:
				return f(a.getType(), std::get<TypeInterface::element<Type::CHAR>>(a.value), std::get<TypeInterface::element<Type::CHAR>>(b.value), args...);
			case Type::BYTE:
				return f(a.getType(), std::get<TypeInterface::element<Type::BYTE>>(a.value), std::get<TypeInterface::element<Type::BYTE>>(b.value), args...);
			case Type::WORD:
				return f(a.getType(), std::get<TypeInterface::element<Type::WORD>>(a.value), std::get<TypeInterface::element<Type::WORD>>(b.value), args...);
			case Type::DWORD:
				return f(a.getType(), std::get<TypeInterface::element<Type::DWORD>>(a.value), std::get<TypeInterface::element<Type::DWORD>>(b.value), args...);
			case Type::QWORD:
				return f(a.getType(), std::get<TypeInterface::element<Type::QWORD>>(a.value), std::get<TypeInterface::element<Type::QWORD>>(b.value), args...);
			case Type::INTEGER:
				return f(a.getType(), std::get<TypeInterface::element<Type::INTEGER>>(a.value), std::get<TypeInterface::element<Type::INTEGER>>(b.value), args...);
			case Type::BOOL:
				return f(a.getType(), std::get<TypeInterface::element<Type::BOOL>>(a.value), std::get<TypeInterface::element<Type::BOOL>>(b.value), args...);
			case Type::REAL:
				return f(a.getType(), std::get<TypeInterface::element<Type::REAL>>(a.value), std::get<TypeInterface::element<Type::REAL>>(b.value), args...);
			case Type::CONTAINER:
				[[fallthrough]]; // Undefined
			case Type::UNKNOWN:
				[[fallthrough]]; // Undefined
			default:
				assert(0);
			}
		}

		template<typename F, typename TObject, typename... Args, typename = std::enable_if_t<std::is_same_v<remove_cvref_t<TObject>, Object>>>
		static auto visit(const F& f, TObject& a, const Args&... args){
			switch(a.getType()){
			case Type::BIT:
				return f(a.getType(), std::get<TypeInterface::element<Type::BIT>>(a.value), args...);
			case Type::CHAR:
				return f(a.getType(), std::get<TypeInterface::element<Type::CHAR>>(a.value), args...);
			case Type::BYTE:
				return f(a.getType(), std::get<TypeInterface::element<Type::BYTE>>(a.value), args...);
			case Type::WORD:
				return f(a.getType(), std::get<TypeInterface::element<Type::WORD>>(a.value), args...);
			case Type::DWORD:
				return f(a.getType(), std::get<TypeInterface::element<Type::DWORD>>(a.value), args...);
			case Type::QWORD:
				return f(a.getType(), std::get<TypeInterface::element<Type::QWORD>>(a.value), args...);
			case Type::INTEGER:
				return f(a.getType(), std::get<TypeInterface::element<Type::INTEGER>>(a.value), args...);
			case Type::BOOL:
				return f(a.getType(), std::get<TypeInterface::element<Type::BOOL>>(a.value), args...);
			case Type::REAL:
				return f(a.getType(), std::get<TypeInterface::element<Type::REAL>>(a.value), args...);
			case Type::CONTAINER:
				[[fallthrough]]; // Undefined
			case Type::UNKNOWN:
				[[fallthrough]]; // Undefined
			default:
				assert(0);
			}
		}
	};
}
