#include "gtest/gtest.h"
#include "object.hpp"
#include "list.hpp"
#include "collection.hpp"

using namespace wiremap;

TEST(ObjectTest, Constructor){
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

TEST(ContainerTest, Constructor){
    List<Integer, 4> ints;
    EXPECT_EQ(ints.size(),4);

    List<Integer,3> ints2 = std::array{1, 2, 3};
    EXPECT_EQ(ints2[2].get(),3);

    List<Integer, 3> ints3 = ints2;
    EXPECT_EQ(ints3[1].get(),ints2[1].get());

    Collection<Integer, Real> t;
    EXPECT_EQ(t.size(),2);

    Collection<Integer, Real> t2 = std::tuple<long, double>{4, 3.5};
    EXPECT_EQ(get<1>(t2).get(),3.5);

    Collection<Collection<Char, Integer>, List<Byte,5>> complex;
    EXPECT_EQ(complex.size(),2);
}

TEST(ContainerTest, AccessTest){
    List<Integer, 4> ints = {0,1,2,3};
    unsigned i = 0;
    for(const auto& a: ints){
        EXPECT_EQ(a.get(), i);
        i++;
    }
}
