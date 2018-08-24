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

    List<Integer,3> ints2 = std::array{1, 2, 3};
    EXPECT_EQ(ints2.internal[2].value,3);

    List<Integer, 3> ints3 = ints2;
    EXPECT_EQ(ints3.internal[1].value,ints2.internal[1].value);

    Collection<Integer, Real> t;
    EXPECT_EQ(t.size,2);

    Collection<Integer, Real> t2 = std::tuple<long, double>{4, 3.5};
    EXPECT_EQ(std::get<1>(t2.internal).value,3.5);

    Collection<Collection<Char, Integer>, List<Byte,5>> complex;
    EXPECT_EQ(complex.size,2);
}
