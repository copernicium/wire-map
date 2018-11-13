#include "gtest/gtest.h"

#include "object.hpp"
#include "visitors.hpp"

using namespace wiremap;

struct ExpectEq{
	template<typename T, typename R, typename = std::enable_if_t<detail::is_wiremap_primitive_v<T>>>
	void operator()(const T& a, const R& b)const{
		EXPECT_EQ(a.require(), b);
		bool same_type = std::is_same_v<typename T::value_type, R>;
		EXPECT_EQ(same_type, true);
	}
};

ExpectEq expect_eq;

TEST(ObjectTest, Constructor){
	Type TYPE = Type::REAL;

	Object a = Object::primitive(TYPE);
	Object::visit(assign, a, 5);

	Object::visit(expect_eq, a, (Real::value_type)5);

	Object b = Object::primitive(TYPE);
	Object::visit(assign, b, 5);

	Object::visit(expect_eq, b, (Real::value_type)5);

	Object c = Object::visit(sum, a, b);
	Object::visit(expect_eq, c, (Real::value_type)(5 + 5));
}

TEST(ObjectTest, List){
	Object list = Object::list(Object::primitive(Type::INTEGER), 10);
	Object::visit(assign, list.at(1), 5);

	for(unsigned i = 0; i < list.size(); i++){
		if(i == 1){
			Object::visit(expect_eq, list.at(i), (Integer::value_type)5);
		} else {
			Object::visit(expect_eq, list.at(i), (Integer::value_type)0);
		}
	}
}

TEST(ObjectTest, Collection){
	Object collection = Object::collection({Object::primitive(Type::REAL), Object::primitive(Type::INTEGER)});
	Object::visit(assign, collection.at(0), (Real::value_type)5);

	Object::visit(expect_eq, collection.at(0), (Real::value_type)5);
	Object::visit(expect_eq, collection.at(1), (Integer::value_type)0);
}

TEST(ObjectTest, Constant){
	const Object a = Object::primitive(Type::REAL, 6.5);
	EXPECT_EQ(Object::visit(compare_equal, a, 6.5), true);
}
