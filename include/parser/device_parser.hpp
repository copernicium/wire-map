#pragma once

#include "map_util.hpp"
#include "parser/parameter_parser.hpp"
#include "parser/constant_parser.hpp"
#include "parser/result_parser.hpp"
#include "parser/tokenizer.hpp"
#include "util.hpp"

namespace wiremap::parser{
    struct DeviceNode{
    private:
        std::string name;

        std::vector<ParameterNode> parameters;
        std::vector<ConstantNode> constants;
        std::vector<ResultNode> results;

		static constexpr std::string_view KEYWORD = "Device";
        static constexpr unsigned KEYWORD_POS = 0;
        static constexpr unsigned REQUIRED_LINE_SIZE = 2;

    public:
		std::string getName()const;

		std::vector<ParameterNode> getParameters()const;
		std::vector<ConstantNode> getConstants()const;
		std::vector<ResultNode> getResults()const;

		int getParameter(const std::string&)const;
		bool isConstant(const std::string&)const;
		bool isResult(const std::string&)const;

        static bool identify(const Line&);
        static DeviceNode parse(const Lines&);

        std::string toString()const;

        DeviceNode();
        DeviceNode(const std::string&, const std::vector<ParameterNode>&, const std::vector<ConstantNode>&, const std::vector<ResultNode>&);

		friend WireMapParser;
    };

    bool operator==(const DeviceNode&, const DeviceNode&);

    struct DeviceNodes{
    private:
        static std::shared_ptr<google::dense_hash_map<wiremap::detail::KeyType,DeviceNode,wiremap::detail::Hasher,wiremap::detail::KeyCompare>> device_nodes;

    public:
        static void reset(){
            device_nodes = std::make_shared<google::dense_hash_map<wiremap::detail::KeyType,DeviceNode,wiremap::detail::Hasher,wiremap::detail::KeyCompare>>();
            device_nodes->set_empty_key(0);
        }

        static void add(const wiremap::detail::KeyType& KEY, const DeviceNode& VALUE)noexcept{
            if(device_nodes == nullptr){
                reset();
            }
            device_nodes->insert(std::make_pair(KEY, VALUE));
        }

        static void add(const std::string& KEY, const DeviceNode& VALUE)noexcept{
            add(hasher(KEY),VALUE);
        }

        static DeviceNode& get(const wiremap::detail::KeyType& KEY)noexcept{
            assert(device_nodes != nullptr && device_nodes->find(KEY) != device_nodes->end());
            return (*device_nodes)[KEY];
        }

        static DeviceNode& get(const std::string& KEY)noexcept{
            return get(hasher(KEY));
        }

        static bool exists(const wiremap::detail::KeyType& KEY)noexcept{
            if(device_nodes == nullptr){
                return false;
            }
            return device_nodes->find(KEY) != device_nodes->end();
        }

        static bool exists(const std::string& KEY)noexcept{
            return exists(hasher(KEY));
        }

        static std::string toString(){
            if(device_nodes == nullptr){
                return "null";
            }
            std::string s = "[";
            for(auto i = device_nodes->begin(); i != device_nodes->end(); ++i){
                if(i != device_nodes->begin()){
                    s += ", ";
                }
                s += i->second.toString();
            }
            s += "]";
            return s;
        }

        static void parse(const Lines& LINES){
            if(LINES.empty() || !DeviceNode::identify(LINES[0])){
                return;
            }
            DeviceNode a = DeviceNode::parse(LINES);
            if(DeviceNodes::exists(a.getName())){
                exit(EXIT_FAILURE); //TODO error, redefinition
            }
            add(a.getName(),a);
        }

        DeviceNodes() = delete;
    };
}
