#!/bin/bash

case "$1" in
    "cmake")
        rm -rf CMakeFiles CMakeCache.txt cmake_install.cmake Makefile;
        ;;
    "wiremap")
        rm -rf bin/tests/* bin/benchmarks/* lib/*;
        ;;
    "external")
        rm -rf external/*;
        ;;
    "all")
        rm -rf CMakeFiles CMakeCache.txt cmake_install.cmake Makefile bin/tests/* bin/benchmarks/* lib/* external;
        ;;
    *)
        printf "Skipping clean. No target specified.\n"
        ;;
esac
