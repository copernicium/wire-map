#include <benchmark/benchmark.h>

#include "parameter.hpp"
#include "result.hpp"
#include "object.hpp"
#include "visitors.hpp"
#include "wiremap.hpp"

using namespace wiremap;

const auto ROBORIO_HASH = hashstr("roborio");
const auto PWM1_HASH = hashstr("pulse_width_1");
const auto SPARK_HASH = hashstr("spark1");
const auto CURRENT_HASH = hashstr("current");

void setup_sample_wiremap(){
	WireMap::reset();
    Result r = std::function<Object(void)>([]{ return Object::primitive((Integer)5); });
    WireMap::add(
        ROBORIO_HASH,
        std::make_pair(PWM1_HASH,r)
	);
}

static void BM_HashStr(benchmark::State& state){
	for(auto _ : state){
		hashstr("roborio");
    }
}

static void BM_ParameterConstructor(benchmark::State& state){
	setup_sample_wiremap();
	for(auto _ : state){
        Parameter p ={ROBORIO_HASH, PWM1_HASH};
    }
}

static void BM_ConstantConstructor(benchmark::State& state){
    for(auto _ : state){
        Constant<Integer> c = 8;
    }
}

static void BM_ResultConstructor(benchmark::State& state){
    for(auto _ : state){
		Result r = std::function<Object(void)>([]{ return Object::primitive((Integer)5); });
    }
}

static void BM_DeviceConstructor0(benchmark::State& state){
    for(auto _ : state){
        Device spark1 ={};
    }
}

static void BM_DeviceConstructor1(benchmark::State& state){
    Parameter p = {ROBORIO_HASH, PWM1_HASH};
	auto member = std::make_pair(PWM1_HASH,p);

    for(auto _ : state){
        Device spark1 ={
			SPARK_HASH,
			member
        };
    }
}

static void BM_DeviceConstructor2(benchmark::State& state){
	setup_sample_wiremap();
    Parameter p ={ROBORIO_HASH, PWM1_HASH};
	auto member1 = std::make_pair(PWM1_HASH,p);

	Result r = std::function<Object(void)>([]{ return Object::primitive((Integer)5); });
	auto member2 = std::make_pair(CURRENT_HASH,r);

    for(auto _ : state){
        Device spark1 ={
			SPARK_HASH,
			member1,
			member2
        };
    }
}

static void BM_DeviceSetup(benchmark::State& state){
    unsigned i = 0;
    for(auto _ : state){
		Result r = std::function<Object(void)>([]{ return Object::primitive((Integer)5); });

        WireMap::add(
            SPARK_HASH + i,
            std::make_pair(CURRENT_HASH,r)
        );

        i++;
    }
    WireMap::reset();
}

static void BM_ParameterAccess(benchmark::State& state){
	setup_sample_wiremap();

    for(auto _ : state){
        Parameter p ={ROBORIO_HASH, PWM1_HASH};
        Object r2 = p.get();

		// std::cout << "value: "<<Object::visit(to_string, r2) << "\n";
    }
}

BENCHMARK(BM_HashStr);

BENCHMARK(BM_ParameterConstructor);
BENCHMARK(BM_ConstantConstructor);
BENCHMARK(BM_ResultConstructor);

BENCHMARK(BM_DeviceConstructor0);
BENCHMARK(BM_DeviceConstructor1);
BENCHMARK(BM_DeviceConstructor2);

BENCHMARK(BM_DeviceSetup);
BENCHMARK(BM_ParameterAccess);

BENCHMARK_MAIN();
