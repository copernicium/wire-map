#include <benchmark/benchmark.h>
#include "object.hpp"
#include "visitors.hpp"

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

static void BM_VisitObject(benchmark::State& state) {
	Object a = Object::primitive(Type::REAL);
	for(auto _ : state){
		Object::visit(assign, a, 5);
	}
}

BENCHMARK(BM_PrimitiveConstructor);
BENCHMARK(BM_ObjectConstructor);
BENCHMARK(BM_VisitObject);
BENCHMARK_MAIN();
