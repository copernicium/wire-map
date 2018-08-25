#include "gtest/gtest.h"

#include "constant.hpp"
#include "accessors.hpp"

using namespace wiremap;

TEST(DeviceTest, ParameterTest){
    Result<Integer> r = {hashstr("spark1"), 5};

    WireMap::get(hashstr("spark1")) = Device();
    WireMap::get(hashstr("spark1")).getResult(hashstr("current")) = std::make_shared<Result<Integer>>(r);

    Parameter<Integer> p = {hashstr("spark1"), hashstr("current")};
    Result<Integer> r2 = getResult(p);

    printf("value:%ld \n",r2.get()->require());
    EXPECT_EQ(r2,r);
}

TEST(DeviceTest, Constructor){
    Device a;
    EXPECT_EQ(0,0); //TODO
}
