#include "gtest/gtest.h"
#include "constant.hpp"

using namespace wiremap;

TEST(ConstantTest, Constructor){
    Constant<Real> a = 6.5;
    EXPECT_EQ(a.value.value, 6.5);

    Constant<Byte> b = 3;
    Constant<Byte> c = b;
    EXPECT_EQ(b.value.value,3);

    Constant<List<Integer,2>> d = std::array{1,2};
    EXPECT_EQ(d.value.internal[1].value, 2);
}
