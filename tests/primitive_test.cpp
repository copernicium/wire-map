#include "gtest/gtest.h"

#include "primitive.hpp"

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
