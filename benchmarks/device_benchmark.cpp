#include <benchmark/benchmark.h>

#include "constant.hpp"
#include "accessors.hpp"

using namespace wiremap;

static void BM_DeviceSetup(benchmark::State& state) {
    for(auto _ : state){
        Result<Integer> r = {hashstr("spark1"), 5};

        WireMap::get(hashstr("spark1")) = Device();
        WireMap::get(hashstr("spark1")).getResult(hashstr("current")) = std::make_shared<Result<Integer>>(r);

        Parameter<Integer> p = {hashstr("spark1"), hashstr("current")};
    }
}

static void BM_ParameterAccess(benchmark::State& state) {
    Result<Integer> r = {hashstr("spark1"), 5};

    WireMap::get(hashstr("spark1")) = Device();
    WireMap::get(hashstr("spark1")).getResult(hashstr("current")) = std::make_shared<Result<Integer>>(r);

    for(auto _ : state){
        Parameter<Integer> p = {hashstr("spark1"), hashstr("current")};
        Result<Integer> r2 = getResult(p);

        // printf("value:%ld \n",r2.get()->require());
    }
}

BENCHMARK(BM_DeviceSetup);
BENCHMARK(BM_ParameterAccess);
BENCHMARK_MAIN();
