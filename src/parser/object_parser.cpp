#include "parser/object_parser.hpp"

#include "parser/util.hpp"

namespace wiremap::parser{
    ObjectNode ObjectNode::parse(const std::string& LINE){
        std::vector<std::string> line = splitLine(LINE);

        if(line.size() < 2){
            return {};
        }

        ObjectNode object_node;
        object_node.name = line[1];
        object_node.type = TypeNode::parse(subvector(line, 0, line.size() - 1));

        return object_node;
    }
}
