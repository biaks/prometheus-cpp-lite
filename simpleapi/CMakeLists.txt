
project(prometheus-cpp-simpleapi)
cmake_minimum_required(VERSION 2.6)

add_library (${PROJECT_NAME} STATIC "./src/simpleapi.cpp")
target_include_directories(${PROJECT_NAME} PUBLIC
 $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
