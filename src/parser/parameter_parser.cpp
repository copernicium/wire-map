#include "parser/parameter_parser.hpp"

#include "parser/util.hpp"
#include <cassert>

namespace wiremap::parser{
    ParameterNode ParameterNode::parse(const std::vector<std::string>& split_line){
        assert(split_line.size() >= 3);

        ParameterNode parameter_node;
        parameter_node.name = split_line[split_line.size() - 1];
        parameter_node.type = Type::parse(std::vector<std::string>{split_line.begin() + 1, split_line.end() - 1});

        return parameter_node;
    }

    ParameterNode ParameterNode::parse(const std::string& LINE){
        return parse(splitLine(LINE));
    }

    std::string ParameterNode::toString()const{
        std::string a = "{";
        a += "name:" + name + ", ";
        a += "type:" + type.toString() + ", ";
        a += "source_device:" + (source_device ? source_device.value() : "null") + ", ";
        a += "source_result:" + (source_result ? source_result.value() : "null");
        a += "}";
        return a;
    }
}
