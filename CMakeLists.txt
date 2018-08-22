cmake_minimum_required(VERSION 3.0.2)

#IF(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
#  MESSAGE(FATAL_ERROR "Vcpkg toolchain not specified. Please run cmake again with -DCMAKE_TOOLCHAIN_FILE=path/to/vcpkg.cmake")
#ENDIF()

project(wire-map)

SET(wire-map_VERSION_MAJOR 1)
SET(wire-map_VERSION_MINOR 0)

FILE(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
FILE(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
FILE(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tests)
FILE(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin/benchmarks)

SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

SET(CMAKE_C_COMPILER gcc)
SET(CMAKE_CXX_COMPILER g++)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra -std=c++17")

if(BUILD_TYPE MATCHES "^[Rr][Ee][Ll][Ee][Aa][Ss][Ee]")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Werror")
else()
  if(NOT BUILD_TYPE MATCHES "^[Dd][Ee][Bb][Uu][Gg]")
    MESSAGE(WARNING "No build type specified; defaulting to debug.")
  endif()
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g")
endif()

ADD_LIBRARY(parser SHARED
  parser/src/parser.cpp
)

TARGET_INCLUDE_DIRECTORIES(parser PRIVATE
  "${CMAKE_BINARY_DIR}/parser/include"
)

ADD_LIBRARY(wiremap SHARED
  src/object.cpp
  )

TARGET_INCLUDE_DIRECTORIES(wiremap PRIVATE
  "${CMAKE_BINARY_DIR}/include"
)
