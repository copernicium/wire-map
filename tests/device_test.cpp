#include "gtest/gtest.h"
#include "device.hpp"
#include "wiremap.hpp"

#include "constant.hpp"
#include "parameter.hpp"
#include "result.hpp"
using namespace wiremap;

TEST(DeviceTest, ParameterTest){
    Result<Integer> r = Integer{5};
    WireMap::get(hashstr("spark1")) = Device();
    WireMap::get(hashstr("spark1")).getResult(hashstr("current")) = std::make_shared<Result<Integer>>(r);
    Parameter<Integer> a = {hashstr("spark1"), hashstr("current")};
    const std::shared_ptr<Result<Integer>> temp = std::dynamic_pointer_cast<Result<Integer>>(a.get());
    Result<Integer> r2 = *temp;
    printf("value:%ld \n",std::dynamic_pointer_cast<Integer>(r2.get())->require());
    EXPECT_EQ(r2,r);
}

TEST(DeviceTest, Constructor){
    Device a;
    EXPECT_EQ(0,0); //TODO
}
