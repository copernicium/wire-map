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

	Object& Object::operator[](const std::size_t& I){
		return at(I);
	}

	const Object& Object::operator[](const std::size_t& I)const{
		return at(I);
	}

	bool Object::empty()const{
		assert(type == Type::CONTAINER);
		return std::get<TypeInterface::element<Type::CONTAINER>>(value).empty();
	}

	Object& Object::front(){
		assert(type == Type::CONTAINER);
		return *(std::get<TypeInterface::element<Type::CONTAINER>>(value).front());
	}

	const Object& Object::front()const{
		assert(type == Type::CONTAINER);
		return *(std::get<TypeInterface::element<Type::CONTAINER>>(value).front());
	}

	Object& Object::back(){
		assert(type == Type::CONTAINER);
		return *(std::get<TypeInterface::element<Type::CONTAINER>>(value).back());
	}

	const Object& Object::back()const{
		assert(type == Type::CONTAINER);
		return *(std::get<TypeInterface::element<Type::CONTAINER>>(value).back());
	}

	TypeInterface::element<Type::CONTAINER>::iterator Object::begin()noexcept{
		assert(type == Type::CONTAINER);
		return std::get<TypeInterface::element<Type::CONTAINER>>(value).begin();
	}

	TypeInterface::element<Type::CONTAINER>::const_iterator Object::begin()const noexcept{
		assert(type == Type::CONTAINER);
		return std::get<TypeInterface::element<Type::CONTAINER>>(value).begin();
	}

	TypeInterface::element<Type::CONTAINER>::iterator Object::end()noexcept{
		assert(type == Type::CONTAINER);
		return std::get<TypeInterface::element<Type::CONTAINER>>(value).end();
	}

	TypeInterface::element<Type::CONTAINER>::const_iterator Object::end()const noexcept{
		assert(type == Type::CONTAINER);
		return std::get<TypeInterface::element<Type::CONTAINER>>(value).end();
	}

	std::size_t Object::size()const noexcept{
		assert(type == Type::CONTAINER);
		return std::get<TypeInterface::element<Type::CONTAINER>>(value).size();
	}

	bool Object::operator==(const Object& B)const{
		if(type != B.type){
			return false;
		}
		if(type == Type::CONTAINER){
			if(size() != B.size()){
				return false;
			}
			for(unsigned i = 0; i < size(); i++){
				if(at(i) != B.at(i)){
					return false;
				}
			}
			return true;
		}
		return value == B.value;
	}

	bool Object::operator!=(const Object& B)const{
		return !(*this == B);
	}
}
