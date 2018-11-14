#include "parser/wiremap_parser.hpp"
#include "parser/device_parser.hpp"
#include "parser/util.hpp"
#include "util.hpp"
#include "object.hpp"
#include "parameter.hpp"
#include "wiremap.hpp"

#include <iostream> // TODO remove

namespace wiremap::parser{
    void WireMapParser::parse(const Lines& LINES){
        for(unsigned i = 0; i < LINES.size(); i++){
            if(LINES[i].getIndentation() == 0){
                const Line& FIRST_LINE = LINES[i];

                const Lines SCOPE = captureScope(LINES, i);
                i += SCOPE.size() - 1; //skip scope in next search

				const std::string& DEVICE_TYPE_NAME = FIRST_LINE[DEVICE_TYPE_POS];

                if(!DeviceNodes::exists(DEVICE_TYPE_NAME)){
                    NYI //TODO error, device not found in project
                }

				const DeviceNode& DEVICE_TYPE = DeviceNodes::get(DEVICE_TYPE_NAME);

                printf("Found:%s\n", DEVICE_TYPE.toString().c_str());

                WireMap::add(DEVICE_TYPE.getName());
				Device device = WireMap::get(DEVICE_TYPE.getName());
				for(unsigned scope_i = 1; scope_i < SCOPE.size(); scope_i++){ // start after first line where device is declared
					const Line& LINE = SCOPE[scope_i];
					// for(const auto& a: LINE){
					// 	std::cout<<"\""<<a<<"\"";
					// }
					// std::cout<<"\n";

					const std::string& MEMBER_NAME = LINE[MEMBER_NAME_POS];

					if(DEVICE_TYPE.isParameter(MEMBER_NAME)){
						assert(LINE[MEMBER_ASSIGNMENT_OPERATOR_POS] == SYMBOLS[PARAMETER_SOURCE]);
						assert(LINE[PARAMETER_SOURCE_SEPARATOR_POS] == SYMBOLS[DOT]);
						device.add(std::make_pair(
									   hasher(MEMBER_NAME),
									   Parameter(LINE[PARAMETER_SOURCE_DEVICE_POS], LINE[PARAMETER_SOURCE_RESULT_POS])
							));
					} else if(DEVICE_TYPE.isConstant(MEMBER_NAME)){
						assert(LINE[MEMBER_ASSIGNMENT_OPERATOR_POS] == SYMBOLS[ASSIGN]);
						// device.add(std::make_pair(
						// 			   hasher(MEMBER_NAME),
						// 			   Object() // TODO
						// 			   ));
					} else if(DEVICE_TYPE.isResult(MEMBER_NAME)){

					} else {
						NYI
					}
				}

				for(const ParameterNode& PARAM: DeviceNodes::get(DEVICE_TYPE_NAME).getParameters()){
					(void)PARAM;
					// WireMap::get(DEVICE_TYPE_NAME).add();
				}
            }
        }
		std::cout << DeviceNodes::toString() << "\n";
        NYI
    }
}
