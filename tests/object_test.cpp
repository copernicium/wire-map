#include "gtest/gtest.h"
#include "object.hpp"

using namespace wiremap;

TEST(ObjectTest, Constructor){
    Integer a;
    EXPECT_EQ(a.default_value, 0);
    EXPECT_EQ(a.valid, false);

    Real b = 6;
    EXPECT_EQ(b.default_value, 0);
    EXPECT_EQ(b.value, 6);
    EXPECT_EQ(b.valid, true);
}

TEST(ContainerTest, Constructor){
    List<Integer, 4> ints;
    EXPECT_EQ(ints.size,4);
    Collection<Integer, Real> t;
    EXPECT_EQ(t.size,2);
    Collection<Collection<Char, Integer>, List<Byte,5>> complex;
    EXPECT_EQ(complex.size,2);
}
