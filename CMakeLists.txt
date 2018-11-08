# Project settings
cmake_minimum_required(VERSION 3.0.2)

PROJECT(wire-map)

INCLUDE(ExternalProject)
SET(EXTERNAL_INSTALL_DIR ${CMAKE_BINARY_DIR}/external)
FILE(MAKE_DIRECTORY ${EXTERNAL_INSTALL_DIR})

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

IF(BUILD_TYPE MATCHES "^[Rr][Ee][Ll][Ee][Aa][Ss][Ee]")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -flto -Werror")
ELSE()
  IF(NOT BUILD_TYPE MATCHES "^[Dd][Ee][Bb][Uu][Gg]")
    MESSAGE(WARNING "No build type specified; defaulting to debug")
  ENDIF()
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g")
ENDIF()

# Install sparsehash

IF(NOT EXISTS ${EXTERNAL_INSTALL_DIR}/sparsehash) # TODO replace with a check with make rather than cmake
  ADD_CUSTOM_TARGET(sparsehash ALL
    COMMAND git clone https://github.com/sparsehash/sparsehash
    COMMAND cd sparsehash && ./configure
    COMMAND cd sparsehash && make
    WORKING_DIRECTORY ${EXTERNAL_INSTALL_DIR}
    VERBATIM)
ELSE()
  MESSAGE("Sparsehash build files found - skipping rebuild\n")
  ADD_CUSTOM_TARGET(sparsehash)
ENDIF()

INCLUDE_DIRECTORIES(SYSTEM ${CMAKE_BINARY_DIR}/external/sparsehash/src)
INCLUDE_DIRECTORIES("${CMAKE_BINARY_DIR}/include")

# Parser Library

ADD_LIBRARY(parser SHARED
  src/parser/init.cpp
  src/parser/util.cpp
  src/parser/type_parser.cpp
  src/parser/object_parser.cpp
  src/parser/parameter_parser.cpp
  src/parser/constant_parser.cpp
  src/parser/result_parser.cpp
  src/parser/device_parser.cpp
  src/parser/wiremap_parser.cpp
  src/parser/project_parser.cpp)

ADD_DEPENDENCIES(parser sparsehash)

TARGET_LINK_LIBRARIES(parser stdc++fs)

# Wire-Map Library

ADD_LIBRARY(wiremap SHARED
  src/object.cpp
  src/result.cpp
  src/parameter.cpp
  src/device.cpp
  src/wiremap.cpp)

ADD_DEPENDENCIES(wiremap sparsehash)

# Install Google Test

IF(TESTING MATCHES "[Tt][Rr][Uu][Ee]" OR TESTING MATCHES "[Oo][Nn]" OR BENCHMARKS MATCHES "[Tt][Rr][Uu][Ee]" OR BENCHMARKS MATCHES "[Oo][Nn]")
  IF(NOT EXISTS ${EXTERNAL_INSTALL_DIR}/lib AND NOT EXISTS ${EXTERNAL_INSTALL_DIR}/lib64)
    EXTERNALPROJECT_ADD(GoogleTest
      PREFIX ${EXTERNAL_INSTALL_DIR}/gtest
      DOWNLOAD_DIR ${EXTERNAL_INSTALL_DIR}
      GIT_REPOSITORY https://github.com/google/googletest
      CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_DIR})
  ELSE()
    MESSAGE("Google test build files found - skipping rebuild\n")
    ADD_CUSTOM_TARGET(GoogleTest)
  ENDIF()

  # Output directories of gtest and benchmark, differs between Windows and Linux so always search both
  LINK_DIRECTORIES(${EXTERNAL_INSTALL_DIR}/lib64)
  LINK_DIRECTORIES(${EXTERNAL_INSTALL_DIR}/lib)
ENDIF()

# Tests

IF(TESTING MATCHES "[Tt][Rr][Uu][Ee]" OR TESTING MATCHES "[Oo][Nn]")
  MESSAGE("Disovering test files:")

  FILE(GLOB test_list tests/*.cpp)
  FOREACH(file ${test_list})
    STRING(REPLACE ".cpp" "" test_name_unclean ${file})
    GET_FILENAME_COMPONENT(test_name ${test_name_unclean} NAME)
    MESSAGE("\tTest \"${test_name}\" found. Generating build target")

    ADD_EXECUTABLE(${test_name} ${file} tests/main_stub.cpp)
    ADD_DEPENDENCIES(${test_name} GoogleTest parser wiremap)

    TARGET_LINK_LIBRARIES(${test_name} wiremap parser pthread gtest gtest_main)
    TARGET_COMPILE_OPTIONS(${test_name} PUBLIC -pthread)
    TARGET_INCLUDE_DIRECTORIES(${test_name} SYSTEM PRIVATE
      "${EXTERNAL_INSTALL_DIR}/include")
    SET_TARGET_PROPERTIES(${test_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/tests")
  ENDFOREACH(file test_list)
  MESSAGE("\n")
ELSE()
  MESSAGE(STATUS "Skipped generation of unit tests")
ENDIF()

# Benchmarks

IF(BENCHMARKS MATCHES "[Tt][Rr][Uu][Ee]" OR BENCHMARKS MATCHES "[Oo][Nn]")
  # Install Benchmark

  IF(NOT EXISTS ${EXTERNAL_INSTALL_DIR}/lib AND NOT EXISTS ${EXTERNAL_INSTALL_DIR}/lib64)
    EXTERNALPROJECT_ADD(Benchmark
      PREFIX ${EXTERNAL_INSTALL_DIR}/benchmark
      GIT_REPOSITORY https://github.com/google/benchmark
      CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_DIR})
  ELSE()
    MESSAGE("Benchmark build files found - skipping rebuild\n")
    ADD_CUSTOM_TARGET(Benchmark)
  ENDIF()
  ADD_DEPENDENCIES(Benchmark GoogleTest)

  MESSAGE("Discovering benchmark files:")

  FILE(GLOB benchmark_list benchmarks/*.cpp)
  FOREACH(file ${benchmark_list})
    STRING(REPLACE ".cpp" "" benchmark_name_unclean ${file})
    GET_FILENAME_COMPONENT(benchmark_name ${benchmark_name_unclean} NAME)
    MESSAGE("\tBenchmark \"${benchmark_name}\" found. Generating build target")

    ADD_EXECUTABLE(${benchmark_name} ${file})
    ADD_DEPENDENCIES(${benchmark_name} Benchmark parser wiremap)

    TARGET_LINK_LIBRARIES(${benchmark_name} wiremap parser pthread benchmark benchmark_main gtest gtest_main)
    TARGET_COMPILE_OPTIONS(${benchmark_name} PUBLIC -pthread)
    TARGET_INCLUDE_DIRECTORIES(${benchmark_name} SYSTEM PRIVATE
      "${EXTERNAL_INSTALL_DIR}/include")
    SET_TARGET_PROPERTIES(${benchmark_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/benchmarks")
  ENDFOREACH(file benchmark_list)
  MESSAGE("\n")
ELSE()
  MESSAGE(STATUS "Skipped generation of benchmarks")
ENDIF()

