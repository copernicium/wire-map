#include "gtest/gtest.h"

#include "object.hpp"
#include "visitors.hpp"

using namespace wiremap;

TEST(PrimitiveTest, Constructor){
    Integer a;
    EXPECT_EQ(a.getDefault(), 0);
    EXPECT_EQ(a.require(), 0);
    EXPECT_EQ((bool)a, false);

    Real b = 6;
    EXPECT_EQ(b.getDefault(), 0);
    EXPECT_EQ(b.require(), 6);
    EXPECT_EQ(b.get(), 6);
    EXPECT_EQ((bool)b, true);
}

TEST(PrimitiveTest, AttributeTest){
    using Ranged = detail::Primitive<int, 0, attributes::Integral<int>, attributes::InRange<int,0,0,10>>; //TODO reduce redundancy in attribute list
    Ranged r = 6;
    EXPECT_EQ(r.get(), 6);
    Ranged r2 = 100;
    EXPECT_EQ(r2.get(), 10);
    Ranged r3 = -10;
    EXPECT_EQ(r3.get(), 0);
}

TEST(PrimitiveTest, AccessTest){
    {
        Integer a = 5;
        Real b = 3;
        Real c = a + b; //TODO this shouldn't be possible. Only allow operations on objects of the same tyoe
        bool d = a == b;
        (void)d;
    }
    //addition
    {
        Integer a = 2;
        Integer b = 3;
        Integer c = a + b;
        EXPECT_EQ(c.get(), a.get() + b.get());
    }
    {
        Integer a;
        Integer b = 3;
        Integer c = a + b;
        EXPECT_EQ((bool)c, false);
    }
    {
        Integer a = 2;
        Integer b;
        Integer c = a + b;
        EXPECT_EQ((bool)c, false);
    }
    {
        Integer a;
        Integer b;
        Integer c = a + b;
        EXPECT_EQ((bool)c, false);
    }
    {
        Integer a = 2;
        Integer b = 2;
        b += a;
        EXPECT_EQ(b.get(), 4);
    }
    {
        Integer a;
        Integer b = 2;
        b += a;
        EXPECT_EQ((bool)b, false);
    }
    {
        Integer a = 2;
        Integer b;
        b += a;
        EXPECT_EQ((bool)b, false);
    }
    {
        Integer a;
        Integer b;
        b += a;
        EXPECT_EQ((bool)b, false);
    }
    //subtraction
    {
        Integer a = 2;
        Integer b = 3;
        Integer c = a - b;
        EXPECT_EQ(c.get(), a.get() - b.get());
    }
    {
        Integer a;
        Integer b = 3;
        Integer c = a - b;
        EXPECT_EQ((bool)c, false);
    }
    {
        Integer a = 2;
        Integer b;
        Integer c = a - b;
        EXPECT_EQ((bool)c, false);
    }
    {
        Integer a;
        Integer b;
        Integer c = a - b;
        EXPECT_EQ((bool)c, false);
    }
    {
        Integer a = 2;
        Integer b = 2;
        b -= a;
        EXPECT_EQ(b.get(), 0);
    }
    {
        Integer a;
        Integer b = 2;
        b -= a;
        EXPECT_EQ((bool)b, false);
    }
    {
        Integer a = 2;
        Integer b;
        b -= a;
        EXPECT_EQ((bool)b, false);
    }
    {
        Integer a;
        Integer b;
        b -= a;
        EXPECT_EQ((bool)b, false);
    }
    //multiplication
    {
        Integer a = 2;
        Integer b = 3;
        Integer c = a * b;
        EXPECT_EQ(c.get(), a.get() * b.get());
    }
    {
        Integer a;
        Integer b = 3;
        Integer c = a * b;
        EXPECT_EQ((bool)c, false);
    }
    {
        Integer a = 2;
        Integer b;
        Integer c = a * b;
        EXPECT_EQ((bool)c, false);
    }
    {
        Integer a;
        Integer b;
        Integer c = a * b;
        EXPECT_EQ((bool)c, false);
    }
    {
        Integer a = 2;
        Integer b = 2;
        b *= a;
        EXPECT_EQ(b.get(), 4);
    }
    {
        Integer a;
        Integer b = 2;
        b *= a;
        EXPECT_EQ((bool)b, false);
    }
    {
        Integer a = 2;
        Integer b;
        b *= a;
        EXPECT_EQ((bool)b, false);
    }
    {
        Integer a;
        Integer b;
        b *= a;
        EXPECT_EQ((bool)b, false);
    }
    //division
    {
        Integer a = 2;
        Integer b = 3;
        Integer c = a / b;
        EXPECT_EQ(c.get(), a.get() / b.get());
    }
    {
        Integer a;
        Integer b = 3;
        Integer c = a / b;
        EXPECT_EQ((bool)c, false);
    }
    {
        Integer a = 2;
        Integer b;
        Integer c = a / b;
        EXPECT_EQ((bool)c, false);
    }
    {
        Integer a;
        Integer b;
        Integer c = a / b;
        EXPECT_EQ((bool)c, false);
    }
    {
        Integer a = 2;
        Integer b = 2;
        b /= a;
        EXPECT_EQ(b.get(), 1);
    }
    {
        Integer a;
        Integer b = 2;
        b /= a;
        EXPECT_EQ((bool)b, false);
    }
    {
        Integer a = 2;
        Integer b;
        b /= a;
        EXPECT_EQ((bool)b, false);
    }
    {
        Integer a;
        Integer b;
        b /= a;
        EXPECT_EQ((bool)b, false);
    }
}

struct ExpectEq{
	template<typename T, typename R, typename = std::enable_if_t<detail::is_wiremap_primitive_v<T>>>
	void operator()(const Type&, const T& a, const R& b)const{
		EXPECT_EQ(a.get(), b);
		bool same_type = std::is_same_v<typename T::value_type, R>;
		EXPECT_EQ(same_type, true);
	}
};

ExpectEq expect_eq;

TEST(ObjectTest, Constructor){
	std::string type_str = "Real";
	Type TYPE = toType(type_str);

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

TEST(ObjectTest, COLLECTION){
	Object collection = Object::collection({Object::primitive(Type::REAL), Object::primitive(Type::INTEGER)});
	Object::visit(assign, collection.at(0), (Real::value_type)5);

	Object::visit(expect_eq, collection.at(0), (Real::value_type)5);
	Object::visit(expect_eq, collection.at(1), (Integer::value_type)0);
}
