#include <benchmark/benchmark.h>

#include "parser/project_parser.hpp"

using namespace wiremap::parser;

static void BM_SplitLine(benchmark::State& state) {
	const std::string LINE_EXAMPLE = "  Parameter   List of 10 Collection of Real, Bool Real Input  ";
    for(auto _ : state){
		Line::tokenize(LINE_EXAMPLE);
	}
}

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

BENCHMARK(BM_SplitLine);
BENCHMARK(BM_ParseDeviceFile);
// BENCHMARK(BM_ParseProject);

BENCHMARK_MAIN();

