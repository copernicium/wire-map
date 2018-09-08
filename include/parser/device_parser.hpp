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

        static DeviceNode parse(std::vector<std::string>&);

        std::string toString()const;
    };


    struct DeviceNodes{
    private:
        static std::shared_ptr<google::dense_hash_map<detail::KeyType,DeviceNode,detail::Hasher,detail::KeyCompare>> device_nodes;

    public:
        static void add(const detail::KeyType& KEY, const DeviceNode& VALUE)noexcept{
            if(device_nodes == nullptr){
                device_nodes = std::make_shared<google::dense_hash_map<detail::KeyType,DeviceNode,detail::Hasher,detail::KeyCompare>>();
                device_nodes->set_empty_key(0);
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

        DeviceNodes() = delete;
    };
}
