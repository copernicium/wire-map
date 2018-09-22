#include "gtest/gtest.h"

#include "parser/parser.hpp"

using namespace wiremap::parser;

TEST(ParserTest, DeviceTest){
    std::vector<std::string> in = readFile("samples/device_sample.txt");
    DeviceNode parsed = DeviceNode::parse(in);
    std::cout<<parsed.toString()<<"\n";
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
    EXPECT_EQ(parsed, expected);
}

TEST(ParserTest, AliasTest){
    parseFile("samples/alias_sample.txt");
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
}
