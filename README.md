# Wire Map

Wire Map is a black-box model, device-mapping tool to specify how data flows and transforms during electronics emulation. Its purpose is to be easily expandable and able to run in near real time as its physical counterpart.

* [Building Wire Map](#building-wire-map)
* [Testing Wire Map](#testing-wire-map)
* [Project Structure](#project-structure)

## Building Wire Map

[![Build Status](https://travis-ci.com/copernicium/wire-map.svg?branch=master)](https://travis-ci.com/copernicium/wire-map)

Wire Map requires GCC 8 or newer. Wire Map only has one dependency and that is sparsehash, which can be installed easily on Linux via the sparsehash package. On Windows, it can be download and built from its GitHub source.

```shell
sudo apt update && sudo apt-get install cmake;
suto apt install sparsehash
```

After the utilities have been installed, all that is left to do is build.

```shell
cmake . -DCMAKE_BUILD_TYPE=RELEASE;
make wiremap;
```

The build mode can be specified using `-DCMAKE_BUILD_MODE=(RELEASE|DEBUG)` to enable or disable debug symbols. To build tests, specify `-DTESTING=(ON|OFF)`. To build benchmarks, specify `-DBENCHMARKS=(ON|OFF)`. Doxygen comments can be built with `-DBUILD_DOC=(ON|OFF)`.

The project can be cleaned using the clean script:

```shell
./clean.sh (all|cmake|wiremap|docs)
```

## Testing Wire Map

Tests and benchmarks build to `bin/tests` and `bin/benchmarks` respectively. To run, execute the following: 

```shell
./bin/tests/test_name                            # Run a given test
./bin/bechmarks/benchmark_name                   # Run a given benchmark
```

## Project Structure

#### benchmarks
This directory contains all of the Google Benchmark benchmarking files for Wire Map.

#### docs
This directory contains a Doxygen Doxyfile and acts as the target for the documentation Doxygen generates.

#### external
This directory contains all of the necessary third party libraries such as Google Test.

#### include
This directory contains all of Wire Map's header files.

#### lib and bin
Wire Map's generated object files build to these directories.

### samples
Example files used in parsing tests.

#### src
This directory contains all of Wire Map's cpp files

#### tests
This directory contains all the Google Test testing files for Wire Map.
