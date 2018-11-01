#include "gtest/gtest.h"
#include "object.hpp"

using namespace wiremap;

TEST(ConstantTest, Constructor){
    Constant<Real> a = 6.5;
    EXPECT_EQ(a.get(), 6.5);

    Constant<Byte> b = 3;
    Constant<Byte> c = b;
    EXPECT_EQ(c.get(),c.get());
}
