#include "gtest/gtest.h"

#include "parameter.hpp"
#include "result.hpp"
#include "visitors.hpp"
#include "wiremap.hpp"

using namespace wiremap;

const std::string SPARK1_STR = "spark1";
const std::string CIM1_STR = "cim1";
const std::string CURRENT_STR = "current";
const std::string COEFFICIENT_STR = "coefficient";

TEST(DeviceTest, AddConstantTest){
	WireMap::reset();
	const Object CONSTANT = Object::primitive(Type::REAL, 5);

    WireMap::add(
        SPARK1_STR,
        std::make_pair(COEFFICIENT_STR,CONSTANT)
	);

    EXPECT_EQ(Object::visit(compare_equal, *WireMap::get(SPARK1_STR).getConstant(COEFFICIENT_STR), CONSTANT), true);
}

TEST(DeviceTest, ParameterTest){
	WireMap::reset();
    Result r = std::function<Object(void)>([]{ return Object::primitive((Integer)5); });

    WireMap::add(
        SPARK1_STR,
        std::make_pair(CURRENT_STR,r)
	);

    Parameter p = {SPARK1_STR, CURRENT_STR};
    Object r2 = p.get();

    EXPECT_EQ(Object::visit(compare_equal, r2, r.get()), true);
}

TEST(DeviceTest, ComplexParameterTest){
	WireMap::reset();

    Result r = std::function<Object(void)>([]{ return Object::primitive((Integer)5); });

    WireMap::add(
        SPARK1_STR,
        std::make_pair(CURRENT_STR,r)
    );

    Parameter p = {SPARK1_STR, CURRENT_STR};

	WireMap::add(
		CIM1_STR,
		std::make_pair(CURRENT_STR, p)
	);

    Object r2 = WireMap::get("cim1").getParameter(CURRENT_STR)->get();

    EXPECT_EQ(Object::visit(compare_equal, r2, r.get()), true);
}

TEST(DeviceTest, Constructor){
    Device a;
    //Fine as long as it compiles
}
