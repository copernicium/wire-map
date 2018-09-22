#pragma once

#include "map_util.hpp"
#include "parser/parameter_parser.hpp"
#include "parser/constant_parser.hpp"
#include "parser/result_parser.hpp"

namespace wiremap::parser{
    struct DeviceNode{
        std::string name;

        std::vector<ParameterNode> parameters;
        std::vector<ConstantNode> constants;
        std::vector<ResultNode> results;

        static constexpr std::string_view KEYWORD = "Device";
        static constexpr unsigned KEYWORD_POS = 0;

        static DeviceNode parse(const std::vector<std::string>&);

        std::string toString()const;

        DeviceNode();
        DeviceNode(const std::string&, const std::vector<ParameterNode>&, const std::vector<ConstantNode>&, const std::vector<ResultNode>&);
    };

    bool operator==(const DeviceNode&, const DeviceNode&);

    struct DeviceNodes{
    private:
        static std::shared_ptr<google::dense_hash_map<detail::KeyType,DeviceNode,detail::Hasher,detail::KeyCompare>> device_nodes;

    public:
        static void reset(){
            device_nodes = std::make_shared<google::dense_hash_map<detail::KeyType,DeviceNode,detail::Hasher,detail::KeyCompare>>();
            device_nodes->set_empty_key(0);
        }

        static void add(const detail::KeyType& KEY, const DeviceNode& VALUE)noexcept{
            if(device_nodes == nullptr){
                reset();
            }
            device_nodes->insert(std::make_pair(KEY, VALUE));
        }

        static void add(const std::string& KEY, const DeviceNode& VALUE)noexcept{
            add(hashstr(KEY),VALUE);
        }

        static DeviceNode& get(const detail::KeyType& KEY)noexcept{
            assert(device_nodes != nullptr && device_nodes->find(KEY) != device_nodes->end());
            return (*device_nodes)[KEY];
        }

        static DeviceNode& get(const std::string& KEY)noexcept{
            return get(hashstr(KEY));
        }

        static bool exists(const detail::KeyType& KEY)noexcept{
            if(device_nodes == nullptr){
                return false;
            }
            return device_nodes->find(KEY) != device_nodes->end();
        }

        static bool exists(const std::string& KEY)noexcept{
            return exists(hashstr(KEY));
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

        DeviceNodes() = delete;
    };
}
