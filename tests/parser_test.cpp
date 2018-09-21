#include "gtest/gtest.h"

#include "parser/parser.hpp"

using namespace wiremap::parser;

TEST(ParserTest, DeviceTest){
    std::vector<std::string> in = readFile("samples/device_sample.txt");
    DeviceNode parsed = DeviceNode::parse(in);
    std::cout<<parsed.toString()<<"\n";
    EXPECT_EQ(parsed.name,"Spark");
    // EXPECT_EQ(parsed.parameters[0],{}); //TODO
    // EXPECT_EQ(parsed.constants[0],{}); //TODO
}

// TEST(ParserTest, AliasTest){
//     std::vector<std::string> in = readFile("samples/alias_sample.txt");
//     DeviceNode parsed = DeviceNode::parse(in);
//     std::cout<<parsed.toString()<<"\n";
//     EXPECT_EQ(0,0); //TODO
// }

TEST(ParserTest, FileTest){
    parseFile("samples/alias_sample.txt");
    EXPECT_EQ(0,0); //TODO
}

