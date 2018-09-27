#include "parser/parameter_parser.hpp"

#include "parser/util.hpp"
#include <cassert>

namespace wiremap::parser{
    ParameterNode ParameterNode::parse(const std::vector<std::string>& split_line){
        assert(split_line.size() >= 3);

        ParameterNode parameter_node;
        parameter_node.name = split_line[split_line.size() - 1];
        parameter_node.type = Type::parse(subvector(split_line, 1, split_line.size() - 1));

        return parameter_node;
    }

    ParameterNode ParameterNode::parse(const std::string& LINE){
        return parse(splitLine(LINE));
    }

    std::string ParameterNode::toString()const{
        std::string a = "{";
        a += "\"name\":\"" + name + "\", ";
        a += "\"type\":" + type.toString() + ", ";
        a += "\"source_device\":" + (source_device ? source_device.value() : "null") + ", ";
        a += "\"source_result\":" + (source_result ? source_result.value() : "null");
        a += "}";
        return a;
    }

    ParameterNode::ParameterNode(){}
    ParameterNode::ParameterNode(const std::string& NAME, const Type& TYPE, const std::optional<std::string>& SD, const std::optional<std::string>& SR): name(NAME), type(TYPE), source_device(SD), source_result(SR){}

    bool operator==(const ParameterNode& a, const ParameterNode& b){
        return a.name == b.name && a.type == b.type && a.source_device == b.source_device && a.source_result == b.source_result;
    }
}
