#include "parser/constant_parser.hpp"

#include "parser/util.hpp"

namespace wiremap::parser{
    std::optional<ConstantNode> parseConstant(const std::string& LINE){
        std::vector<std::string> split_line = splitLine(LINE);

        if(split_line.size() < 3){
            return {};
        }

        std::optional<Type> type = parseType(split_line[0]);
        if(!type){
            return {};
        }

        std::string name = split_line[1];

        ConstantNode constant_node;
        constant_node.name = name;
        constant_node.type = type.value();

        return {constant_node};
    }
}
