#include "gtest/gtest.h"
#include "object.hpp"

using namespace wiremap;

TEST(ObjectTest, Constructor){
    Object<int,0> a;
    EXPECT_EQ(a.default_value, 0);
    EXPECT_EQ(a.valid, false);

    Object<double,0> b = 6;
    EXPECT_EQ(b.default_value, 0);
    EXPECT_EQ(b.value, 6);
    EXPECT_EQ(b.valid, true);
}

TEST(ContainerTest, Constructor){
    List<Integer, 4> ints;
    Collection<Integer, Real> t;
    EXPECT_EQ(0,0); //as long as this compiles it passes
}
