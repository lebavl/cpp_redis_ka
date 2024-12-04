cmake_minimum_required(VERSION 3.26)

# Include Google Benchmark
find_package(benchmark REQUIRED PATHS C:/tools/benchmark/build )

# Add source to this project's executable.
add_executable (StringBenchmarks "StringBenchmarks.cpp" "StringBenchmarks.h")

find_package(Threads REQUIRED)
target_link_libraries(StringBenchmarks Threads::Threads)
# Link Google Benchmark to the project
target_link_libraries(StringBenchmarks benchmark::benchmark)
SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -lbenchmark")

# Link Shlwapi to the project
if ("${CMAKE_SYSTEM_NAME}" MATCHES "Windows")
    target_link_libraries(StringBenchmarks Shlwapi)
endif()