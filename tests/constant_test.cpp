#include "gtest/gtest.h"
#include "types.hpp"

using namespace wiremap;

TEST(ConstantTest, Constructor){
    Constant<Real> a = 6.5;
    EXPECT_EQ(a.get(), 6.5);

    Constant<Byte> b = 3;
    Constant<Byte> c = b;
    EXPECT_EQ(c.get(),c.get());

    Constant<List<Integer,2>> d = std::array<long,2>{1,2};
    EXPECT_EQ(d[1].get(), 2);

    Constant<Collection<Real>> e= std::tuple<double>{4.3};
    EXPECT_EQ(get<0>(e).get(),4.3);
}
