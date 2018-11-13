#include "parser/result_parser.hpp"

#include "parser/util.hpp"
#include <cassert>

namespace wiremap::parser{
	std::string ResultNode::getName()const{
		return name;
	}

	TypeNode ResultNode::getType()const{
		return type;
	}

	bool ResultNode::identify(const Line& LINE){
		return LINE.size() >= MIN_DECLARATION_TERMS && LINE.front() == KEYWORD;
	}

    ResultNode ResultNode::parse(const Line& LINE){
        assert(LINE.size() >= MIN_DECLARATION_TERMS);

        ResultNode result_node;
        result_node.name = LINE[LINE.size() - 1];
        result_node.type = TypeNode::parse(LINE.segment(1, LINE.size() - 1));
        //TODO generating function
        return result_node;
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

	ResultNode::ResultNode(const std::string& NAME, const TypeNode& TYPE): name(NAME), type(TYPE){}

    bool operator==(const ResultNode& a, const ResultNode& b){
        return a.getName() == b.getName() && a.getType() == b.getType();
    }
}
