#include "parser/object_parser.hpp"

#include "parser/util.hpp"

namespace wiremap::parser{
    std::optional<ObjectNode> parseObject(const std::string& LINE){
        std::vector<std::string> split_line = splitLine(LINE);

        if(split_line.size() < 2){
            return {};
        }

        std::optional<Type> type = parseType(split_line[0]);
        if(!type){
            return {};
        }

        std::string name = split_line[1];

        ObjectNode object_node;
        object_node.name = name;
        object_node.type = type.value();

        return {object_node};
    }
}
