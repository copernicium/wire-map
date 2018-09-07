#include "parser/parameter_parser.hpp"

#include "parser/util.hpp"

namespace wiremap::parser{
    std::optional<ParameterNode> parseParameter(const std::vector<std::string>& split_line){
        if(split_line.size() < 3){
            return {};
        }

        std::optional<Type> type = parseType(std::vector<std::string>{split_line.begin() + 1, split_line.end() - 1});
        if(!type){
            return {};
        }

        std::string name = split_line[split_line.size() - 1];

        ParameterNode parameter_node;
        parameter_node.name = name;
        parameter_node.type = type.value();

        return {parameter_node};
    }

    std::optional<ParameterNode> parseParameter(const std::string& LINE){
        std::vector<std::string> split_line = splitLine(LINE);
        return parseParameter(split_line);

    }
}
