#include "gtest/gtest.h"

#include "types.hpp"
#include "accessors.hpp"

using namespace wiremap;

TEST(DeviceTest, ParameterTest){
    Result<Integer> r = {hashstr("spark1"), 5};

    WireMap::get(hashstr("spark1")) = Device(
        std::make_pair(hashstr("current"),std::make_shared<Result<Integer>>(r))
    );

    Parameter<Integer> p = {hashstr("spark1"), hashstr("current")};
    Result<Integer> r2 = getResult(p);

    EXPECT_EQ(r2,r);
    EXPECT_EQ(r2.get()->require(),5);
}

TEST(DeviceTest, Constructor){
    Device a;
    //Fine as long as it compiles
}
