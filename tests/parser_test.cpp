#include "gtest/gtest.h"

#include "parser/parser.hpp"

using namespace wiremap::parser;

TEST(ParserTest, DeviceTest){
    std::vector<std::string> in = readFile("samples/device_sample.txt");
    std::optional<DeviceNode> parsed = parseDevice(in);
    if(parsed){
        DeviceNode device_node = parsed.value();
        std::cout<<device_node.name<<"\n";
    }
    EXPECT_EQ(0,0); //TODO
}
