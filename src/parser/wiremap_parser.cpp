#include "parser/wiremap_parser.hpp"
#include "parser/device_parser.hpp"
#include "parser/util.hpp"
#include "util.hpp"
#include "object.hpp"
#include "wiremap.hpp"

#include <iostream> // TODO remove

namespace wiremap::parser{
    void WireMapParser::parse(const Lines& LINES){
        for(unsigned i = 0; i < LINES.size(); i++){
            if(LINES[i].getIndentation() == 0){
                const Line& first_line = LINES[i];

                Lines scope = captureScope(LINES, i);
                i += scope.size() - 1; //skip scope in next search

				std::string device_type_name = first_line[DEVICE_TYPE_POS];

                if(!DeviceNodes::exists(device_type_name)){
                    NYI //TODO error, device not found in project
                }

                printf("Found:%s\n", DeviceNodes::get(device_type_name).toString().c_str());

                WireMap::add(device_type_name);
				for(unsigned scope_i = 1; scope_i < scope.size(); scope_i++){ // start after first line where device is declared
					const Line& split_line = scope[scope_i];
					// for(const auto& a: split_line){
					// 	std::cout<<"\""<<a<<"\"";
					// }
					// std::cout<<"\n";

					assert(DeviceNodes::exists(device_type_name));
					int parameter_pos = DeviceNodes::get(device_type_name).getParameter(split_line[MEMBER_NAME_POS]);


					if(parameter_pos != -1){
						assert(split_line[PARAMETER_SOURCE_SEPARATOR_POS] == SYMBOLS[DOT]);
						DeviceNodes::get(device_type_name).parameters[parameter_pos].source_device = split_line[PARAMETER_SOURCE_DEVICE_POS];
						DeviceNodes::get(device_type_name).parameters[parameter_pos].source_result = split_line[PARAMETER_SOURCE_RESULT_POS];
					} else if(DeviceNodes::get(device_type_name).isConstant(split_line[MEMBER_NAME_POS])){

					} else if(DeviceNodes::get(device_type_name).isResult(split_line[MEMBER_NAME_POS])){

					} else {
						NYI
					}
				}

				for(const ParameterNode& PARAM: DeviceNodes::get(device_type_name).getParameters()){
					(void)PARAM;
					// WireMap::get(device_type_name).add();
				}
            }
        }
		std::cout << DeviceNodes::toString() << "\n";
        NYI
    }
}
