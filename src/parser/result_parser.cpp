#include "parser/result_parser.hpp"

#include "parser/util.hpp"
#include <cassert>

namespace wiremap::parser{
	std::string ResultNode::getName()const{
		return name;
	}

	Type ResultNode::getType()const{
		return type;
	}

	bool ResultNode::identify(const std::vector<std::string>& LINE){
		return LINE.size() >= 3 && LINE.front() == KEYWORD;
	}

    ResultNode ResultNode::parse(const std::vector<std::string>& split_line){
        assert(split_line.size() >= 3);

        ResultNode result_node;
        result_node.name = split_line[split_line.size() - 1];
        result_node.type = Type::parse(subvector(split_line, 1, split_line.size() - 1));
        //TODO generating function
        return result_node;
    }

    ResultNode ResultNode::parse(const std::string& LINE){
        return parse(splitLine(LINE));
    }

    std::string ResultNode::toString()const{
        std::string a = "{";
        a += "\"name\":\"" + name + "\", ";
        a += "\"type\":" + type.toString();
        //TODO generating function
        a += "}";
        return a;
    }

    ResultNode::ResultNode(){}
    ResultNode::ResultNode(const std::string& NAME, const Type& TYPE): name(NAME), type(TYPE){}

    bool operator==(const ResultNode& a, const ResultNode& b){
        return a.getName() == b.getName() && a.getType() == b.getType();
    }
}
