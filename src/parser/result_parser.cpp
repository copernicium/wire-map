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
		return LINE.size() >= MIN_DECLARATION_TERMS && LINE.front() == KEYWORD;
	}

    ResultNode ResultNode::parse(const std::vector<std::string>& LINE){
        assert(LINE.size() >= MIN_DECLARATION_TERMS);

        ResultNode result_node;
        result_node.name = LINE[LINE.size() - 1];
        result_node.type = Type::parse(subvector(LINE, 1, LINE.size() - 1));
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
