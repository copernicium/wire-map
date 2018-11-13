#include "parser/object_parser.hpp"

#include "parser/util.hpp"

namespace wiremap::parser{
    ObjectNode ObjectNode::parse(const Line& LINE){
        if(LINE.size() < 2){
            return {};
        }

        ObjectNode object_node;
        object_node.name = LINE[1];
        object_node.type = TypeNode::parse(LINE.segment(0, LINE.size() - 1));

        return object_node;
    }
}
