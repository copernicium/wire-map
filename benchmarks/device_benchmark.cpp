#include <benchmark/benchmark.h>

#include "parameter.hpp"
#include "result.hpp"
#include "object.hpp"
#include "wiremap.hpp"

using namespace wiremap;


void setup_sample_wiremap(){
	WireMap::reset();
	Result<Integer> r= std::function<Integer(void)>([]{ return 5; });
    WireMap::add(
        "roborio",
        std::make_pair("pulse_width_1",r)
	);
}

static void BM_ParameterConstructor(benchmark::State& state) {
	setup_sample_wiremap();
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
	auto member = std::make_pair("pulse_width_1",p);

    for(auto _ : state){
        Device spark1 = {
			"spark1",
			member
        };
    }
}

static void BM_DeviceConstructor2(benchmark::State& state) {
	setup_sample_wiremap();
    Parameter<Integer> p = {"roborio", "pulse_width_1"};
	auto member1 = std::make_pair("pulse_width_1",p);

	Result<Integer> r = std::function<Integer(void)>([]{ return 5; });
	auto member2 = std::make_pair("current",r);

    for(auto _ : state){
        Device spark1 = {
			"spark1",
			member1,
			member2
        };
    }
}

static void BM_DeviceSetup(benchmark::State& state) {
    unsigned i = 0;
    for(auto _ : state){
        Result<Integer> r = std::function<Integer(void)>([]{ return 5; });

        WireMap::add(
            "spark" + std::to_string(i),
            std::make_pair("current",r)
        );

        i++;
    }
    WireMap::reset();
}

static void BM_ParameterAccess(benchmark::State& state) {
	setup_sample_wiremap();

    for(auto _ : state){
        Parameter<Integer> p = {"roborio", "pulse_width_1"};
        Integer r2 = p.get();

        // printf("value:%ld \n",r2.require());
    }
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
