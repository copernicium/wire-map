#include <benchmark/benchmark.h>

#include "types.hpp"
#include "accessors.hpp"

using namespace wiremap;

static void BM_DeviceConstructor0(benchmark::State& state) {
    for(auto _ : state){
        Device spark1 = {};
    }
}

static void BM_DeviceConstructor1(benchmark::State& state) {
    Parameter<Integer> p = {hashstr("roborio"), hashstr("pulse_width_1")};
    for(auto _ : state){
        Device spark1 = {
            std::make_pair(hashstr("pulse_width_1"),std::make_shared<Parameter<Integer>>(p))
        };
    }
}

static void BM_DeviceConstructor2(benchmark::State& state) {
    Parameter<Integer> p = {hashstr("roborio"), hashstr("pulse_width_1")};
    Result<Integer> r = {hashstr("spark1"), 5};
    for(auto _ : state){
        Device spark1 = {
            std::make_pair(hashstr("pulse_width_1"),std::make_shared<Parameter<Integer>>(p)),
            std::make_pair(hashstr("current"),std::make_shared<Result<Integer>>(r))
        };
    }
}

static void BM_DeviceSetup(benchmark::State& state) {
    for(auto _ : state){
        Result<Integer> r = {hashstr("spark1"), 5};

        WireMap::get(hashstr("spark1")) = Device(
            std::make_pair(hashstr("current"),std::make_shared<Result<Integer>>(r))
        );

        Parameter<Integer> p = {hashstr("spark1"), hashstr("current")};
    }
}

static void BM_ParameterAccess(benchmark::State& state) {
    Result<Integer> r = {hashstr("spark1"), 5};

    WireMap::get(hashstr("spark1")) = Device(
        std::make_pair(hashstr("current"),std::make_shared<Result<Integer>>(r))
    );

    for(auto _ : state){
        Parameter<Integer> p = {hashstr("spark1"), hashstr("current")};
        Result<Integer> r2 = getResult(p);

        // printf("value:%ld \n",r2.get()->require());
    }
}

BENCHMARK(BM_DeviceConstructor0);
BENCHMARK(BM_DeviceConstructor1);
BENCHMARK(BM_DeviceConstructor2);
BENCHMARK(BM_DeviceSetup);
BENCHMARK(BM_ParameterAccess);
BENCHMARK_MAIN();
