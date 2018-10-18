#include <benchmark/benchmark.h>

#include "parameter.hpp"
#include "result.hpp"
#include "types.hpp"
#include "wiremap.hpp"

using namespace wiremap;

static void BM_ParameterConstructor(benchmark::State& state) {
    for(auto _ : state){
        Parameter<Integer> p = {"roborio", "pulse_width_1"};
    }
}

static void BM_ConstantConstructor(benchmark::State& state) {
    for(auto _ : state){
        Constant<Integer> c = 8;
    }
}

static void BM_ResultConstructor(benchmark::State& state) {
    for(auto _ : state){
        Result<Integer> r = std::function<Integer(void)>([]{ return 5; });
    }
}

static void BM_DeviceConstructor0(benchmark::State& state) {
    for(auto _ : state){
        Device spark1 = {};
    }
}

static void BM_DeviceConstructor1(benchmark::State& state) {
    Parameter<Integer> p = {"roborio", "pulse_width_1"};
    for(auto _ : state){
        Device spark1 = {
            std::make_pair("pulse_width_1",p)
        };
    }
}

static void BM_DeviceConstructor2(benchmark::State& state) {
    Parameter<Integer> p = {"roborio", "pulse_width_1"};
    Result<Integer> r = std::function<Integer(void)>([]{ return 5; });
    for(auto _ : state){
        Device spark1 = {
            std::make_pair("pulse_width_1",p),
            std::make_pair("current",r)
        };
    }
    WireMap::reset();
}

static void BM_DeviceSetup(benchmark::State& state) {
    unsigned i = 0;
    for(auto _ : state){
        Result<Integer> r = std::function<Integer(void)>([]{ return 5; });

        WireMap::add(
            "spark" + std::to_string(i),
            std::make_pair("current",r)
        );

        Parameter<Integer> p = {"spark1", "current"};
        i++;
    }
    WireMap::reset();
}

static void BM_ParameterAccess(benchmark::State& state) {
    Result<Integer> r = std::function<Integer(void)>([]{ return 5; });

    WireMap::add(
        "spark1",
        std::make_pair("current",r)
    );

    for(auto _ : state){
        Parameter<Integer> p = {"spark1", "current"};
        Result<Integer> r2 = p.get();

        // printf("value:%ld \n",r2.get()->require());
    }
    WireMap::reset();
}

BENCHMARK(BM_ParameterConstructor);
BENCHMARK(BM_ConstantConstructor);
BENCHMARK(BM_ResultConstructor);

BENCHMARK(BM_DeviceConstructor0);
BENCHMARK(BM_DeviceConstructor1);
BENCHMARK(BM_DeviceConstructor2);

BENCHMARK(BM_DeviceSetup);
BENCHMARK(BM_ParameterAccess);

BENCHMARK_MAIN();
