cmake_minimum_required(VERSION 3.26)
project(cpp_redis_ka)

set(CMAKE_CXX_STANDARD 23)

add_executable(cpp_redis_ka main.cpp)
SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -lws2_32")
target_link_libraries(cpp_redis_ka wsock32 ws2_32)

add_subdirectory ("benchmarks")