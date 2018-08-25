#include <benchmark/benchmark.h>
#include "object.hpp"

using namespace wiremap;

static void BM_ObjectConstructor(benchmark::State& state) {
    for(auto _ : state){
        Real a;
    }
}

BENCHMARK(BM_ObjectConstructor);
BENCHMARK_MAIN();
