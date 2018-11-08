#include "gtest/gtest.h"

#include "parameter.hpp"
#include "result.hpp"
#include "visitors.hpp"
#include "wiremap.hpp"

using namespace wiremap;

TEST(DeviceTest, ParameterTest){
    Result r = std::function<Object(void)>([]{ return Object::primitive((Integer)5); });

    WireMap::add(
        "spark1",
        std::make_pair("current",r)
	);

    Parameter p = {"spark1", "current"};
    Object r2 = p.get();

    EXPECT_EQ(Object::visit(compare_equal, r2, r.get()), true);
}

TEST(DeviceTest, ComplexParameterTest){
	WireMap::reset();

    Result r = std::function<Object(void)>([]{ return Object::primitive((Integer)5); });

    WireMap::add(
        "spark1",
        std::make_pair("current",r)
    );

    Parameter p = {"spark1", "current"};

	WireMap::add(
		"cim1",
		std::make_pair("current", p)
	);

    Object r2 = WireMap::get("cim1").getParameter("current")->get();

    EXPECT_EQ(Object::visit(compare_equal, r2, r.get()), true);
}

TEST(DeviceTest, Constructor){
    Device a;
    //Fine as long as it compiles
}
