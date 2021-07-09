
project(prometheus-cpp-lite-core)
cmake_minimum_required(VERSION 2.6)

file(GLOB_RECURSE PROMETHEUS_CPP_LITE_HEADERS *.h)

add_library               (${PROJECT_NAME}     INTERFACE)
target_include_directories(${PROJECT_NAME}     INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)


target_sources            (${PROJECT_NAME}     INTERFACE ${PROMETHEUS_CPP_LITE_HEADERS}) # add "prometheus" node to each target
add_custom_target         (${PROJECT_NAME}-ide SOURCES   ${PROMETHEUS_CPP_LITE_HEADERS}) # add "prometheus-ide" target

set                       (${PROJECT_NAME}_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include PARENT_SCOPE) # set path to headers in parent scope
