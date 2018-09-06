#include "gtest/gtest.h"

#include "parser/parser.hpp"

using namespace wiremap::parser;

TEST(ParserTest, DeviceTest){
    std::vector<std::string> in = readFile("samples/device_sample.txt");
    parseDevice(in);
    EXPECT_EQ(0,0); //TODO
}
