#include "gtest/gtest.h"

#include "types.hpp"
#include "accessors.hpp"

using namespace wiremap;

TEST(DeviceTest, ParameterTest){
    Result<Integer> r = std::function<Integer(void)>([]{ return 5; });

    WireMap::add(
        hashstr("spark1"),
        std::make_pair(hashstr("current"),r)
    );

    Parameter<Integer> p = {hashstr("spark1"), hashstr("current")};
    Result<Integer> r2 = getResult(p);

    EXPECT_EQ(r2.get()->require(),5);
}

TEST(DeviceTest, Constructor){
    Device a;
    //Fine as long as it compiles
}
