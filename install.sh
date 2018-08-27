#!/bin/bash

if [ $# -eq 0 ]; then
	printf "VCPKG install directory not specified; please run again with directory to install it at\n"
	exit 1
fi

VCPKG=$1

if [ ! -d $VCPKG ]; then
	git clone https://github.com/Microsoft/vcpkg.git $VCPKG
fi

cd $VCPKG

if [ ! -f "vcpkg" ]; then
	./bootstrap-vcpkg.sh
fi

until [ -f vcpkg ]; do
    printf "vcpkg still building\n"
    sleep 3
done

./vcpkg install gtest
./vcpkg install benchmark

printf "\nInstalled vckpg with packages gtest and benchmark\n"

printf "Also install package libsparsehash-dev\n"

printf "\nRun CMake with -DCMAKE_TOOLCHAIN_FILE=$VCPKG/scripts/buildsystems/vcpkg.cmake\n"
