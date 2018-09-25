#include "gtest/gtest.h"

#include "parser/project_parser.hpp"

using namespace wiremap::parser;

TEST(ParserTest, DeviceTest){
    Project::parseFile("samples/device_sample.wm");
    std::cout<<"\"DeviceNodes\":"<<DeviceNodes::toString()<<"\n";
    DeviceNode expected = {
        "Spark",
        {
            {"VoltageIn",{Type::UnderlyingType::BOOL,10}, {}, {}}
        },
        {
            {"Coefficient",{Type::UnderlyingType::REAL}, {}}
        },
        {}
    };
    EXPECT_EQ(DeviceNodes::get("Spark"), expected);
    DeviceNodes::reset();
}

TEST(ParserTest, AliasTest){
    Project::parseFile("samples/alias_sample.wm");
    std::cout<<"\"DeviceNodes\":"<<DeviceNodes::toString()<<"\n";
    DeviceNode expected = {
        "Person",
        {},
        {
            {"Contact",{Type::UnderlyingType::INTEGER, 10}, {}}
        },
        {}
    };
    EXPECT_EQ(DeviceNodes::get("Person"), expected);
    DeviceNodes::reset();
}

TEST(ParserTest, ProjectTest){
    Project::parse("samples/project/");
    std::cout<<"\"DeviceNodes\":"<<DeviceNodes::toString()<<"\n";
    EXPECT_EQ(0, 0); //TODO
    DeviceNodes::reset();
}
