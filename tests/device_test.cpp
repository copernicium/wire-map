#include "gtest/gtest.h"

#include "parameter.hpp"
#include "result.hpp"
#include "types.hpp"
#include "wiremap.hpp"

using namespace wiremap;

TEST(DeviceTest, ParameterTest){
    Result<Integer> r = std::function<Integer(void)>([]{ return 5; });

    WireMap::add(
        "spark1",
        std::make_pair("current",r)
    );

    Parameter<Integer> p = {"spark1", "current"};
    Result<Integer> r2 = p.get();

    EXPECT_EQ(r2.get().require(), 5);
}

TEST(DeviceTest, Constructor){
    Device a;
    //Fine as long as it compiles
}
