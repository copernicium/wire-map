#include <benchmark/benchmark.h>
#include "object.hpp"

using namespace wiremap;

static void BM_PrimitiveConstructor(benchmark::State& state) {
    for(auto _ : state){
        Real a;
    }
}

static void BM_ObjectConstructor(benchmark::State& state) {
    for(auto _ : state){
        Object a = Object::primitive(Type::REAL);
    }
}

BENCHMARK(BM_PrimitiveConstructor);
BENCHMARK(BM_ObjectConstructor);
BENCHMARK_MAIN();
