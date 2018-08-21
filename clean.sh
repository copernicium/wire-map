#!/bin/bash

case "$1" in
    "cmake")
        rm -rf CMakeFiles CMakeCache.txt cmake_install.cmake Makefile;
        ;;
    "wiremap")
        rm -rf build/* lib/*;
        ;;
    "all")
        rm -rf CMakeFiles CMakeCache.txt cmake_install.cmake Makefile build/* lib/*;
        ;;
    *)
        printf "Skipping clean. No target specified.\n"
        ;;
esac
