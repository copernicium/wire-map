#include "parser/object_parser.hpp"

#include "parser/util.hpp"

namespace wiremap::parser{
    ObjectNode ObjectNode::parse(const std::string& LINE){
        std::vector<std::string> split_line = splitLine(LINE);

        if(split_line.size() < 2){
            return {};
        }

        ObjectNode object_node;
        object_node.name = split_line[1];
        object_node.type = Type::parse(subvector(split_line, 0, split_line.size() - 1));

        return object_node;
    }
}
