#include <benchmark/benchmark.h>

#include "parser/project_parser.hpp"

using namespace wiremap::parser;

static void BM_ParseDeviceFile(benchmark::State& state) {
    for(auto _ : state){
		Project::parseFile("samples/device_sample.hpp");
		DeviceNodes::reset();
	}
}

// static void BM_ParseProject(benchmark::State& state) { //TODO
//     for(auto _ : state){
// 		Project::parse("samples/simple-frc/");
// 		DeviceNodes::reset();
// 	}
// }

BENCHMARK(BM_ParseDeviceFile);
// BENCHMARK(BM_ParseProject);

BENCHMARK_MAIN();

