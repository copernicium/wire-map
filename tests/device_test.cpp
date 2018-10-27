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
    Integer r2 = p.get();

    EXPECT_EQ(r2.require(), r.get().require());
}

TEST(DeviceTest, ComplexParameterTest){
	WireMap::reset();

    Result<Integer> r = std::function<Integer(void)>([]{ return 5; });

    WireMap::add(
        "spark1",
        std::make_pair("current",r)
    );

    Parameter<Integer> p = {"spark1", "current"};

	WireMap::add(
		"cim1",
		std::make_pair("current", p)
	);

    Integer r2 = WireMap::get("cim1").getParameter("current");

    EXPECT_EQ(r2.require(), r.get().require());
}

TEST(DeviceTest, TypeInterpretation){
}

TEST(DeviceTest, Constructor){
    Device a;
    //Fine as long as it compiles
}
