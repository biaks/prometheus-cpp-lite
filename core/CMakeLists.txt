
project(prometheus-cpp-lite-core)
cmake_minimum_required(VERSION 2.6)

file(GLOB_RECURSE PROMETHEUS_CPP_LITE_HEADERS *.h)

add_library               (${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_custom_target         (${PROJECT_NAME}_ide SOURCES ${PROMETHEUS_CPP_LITE_HEADERS})
