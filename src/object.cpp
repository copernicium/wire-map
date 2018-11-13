#include "object.hpp"

namespace wiremap{
	Object::Object(const Type& TYPE)noexcept: type(TYPE), value(TypeInterface::create(type)){}

	Object::Object(const Object& TYPE, const std::size_t& SIZE)noexcept: Object(Type::CONTAINER){
		std::get<TypeInterface::element<Type::CONTAINER>>(value).reserve(SIZE);
		for(unsigned i = 0; i < SIZE; i++){
			std::get<TypeInterface::element<Type::CONTAINER>>(value).push_back(TYPE.clone());
		}
	}

	Object::Object(const std::vector<Object>& TYPES)noexcept: Object(Type::CONTAINER){
		std::get<TypeInterface::element<Type::CONTAINER>>(value).reserve(TYPES.size());
		for(unsigned i = 0; i < TYPES.size(); i++){
			std::get<TypeInterface::element<Type::CONTAINER>>(value).push_back(TYPES.at(i).clone());
		}
	}

	Object::Object(const Object& OTHER)noexcept: type(OTHER.type), value(OTHER.value){ // Don't copy over container's vector just to rewrite it
		if(type == Type::CONTAINER){
			for(unsigned i = 0; i < size(); i++){
				std::get<TypeInterface::element<Type::CONTAINER>>(value).at(i) = OTHER.at(i).clone();
			}
		}
	}

	Object& Object::operator=(const Object& OTHER)noexcept{ // TODO ensure underlying types are same?
		if(&OTHER == this){
			return *this;
		}
		type = OTHER.type;
		value = OTHER.value;
		if(type == Type::CONTAINER){
			for(unsigned i = 0; i < size(); i++){
				std::get<TypeInterface::element<Type::CONTAINER>>(value).at(i) = OTHER.at(i).clone();
				}
		}
		return *this;
	}

	Object& Object::operator=(Object&& other)noexcept{
		assert(&other != this);
		type = std::move(other.type);
		value = std::move(other.value);
		return *this;
	}

	Object Object::primitive(const Type& TYPE)noexcept{
		assert(TYPE != Type::CONTAINER);
		return Object(TYPE);
	}

	Object Object::list(const Object& TYPE, const std::size_t& SIZE)noexcept{
		return Object(TYPE, SIZE);
	}

	Object Object::collection(const std::vector<Object>& TYPES)noexcept{
		return Object(TYPES);
	}

	std::shared_ptr<Object> Object::clone()const noexcept{
		return std::make_shared<Object>(*this);
	}

	const Type& Object::getType()const noexcept{
		return type;
	}

	Object& Object::at(const std::size_t& I){
		assert(type == Type::CONTAINER);
		return *(std::get<TypeInterface::element<Type::CONTAINER>>(value)).at(I);
	}

	const Object& Object::at(const std::size_t& I)const{
		assert(type == Type::CONTAINER);
		return *(std::get<TypeInterface::element<Type::CONTAINER>>(value)).at(I);
	}

	std::size_t Object::size()const noexcept{
		assert(type == Type::CONTAINER);
		return std::get<TypeInterface::element<Type::CONTAINER>>(value).size();
	}

	bool Object::operator==(const Object& B)const{
		return type == B.type && value == B.value;
	}
}
