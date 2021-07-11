
project(prometheus-cpp-lite)
cmake_minimum_required(VERSION 2.6)

option(PROMETHEUS_BUILD_EXAMPLES "Build with examples" OFF)

if(WIN32)

  # This properties specifies the directories into which targets files should be built
  set(EXECUTABLE_OUTPUT_PATH         ${PROJECT_SOURCE_DIR}/bin) # Set old executable location variable
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin) # Set new executable location variable. Then it can be read from RUNTIME_OUTPUT_DIRECTORY variable.

  # it prevent create Debug/ and Release folders in Visual Studio
  foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${PROJECT_SOURCE_DIR}/bin )
  endforeach()

  set (INSTALL_PATH_BIN "${PROJECT_SOURCE_DIR}/installed/bin/")

else() # not WIN32

  set (INSTALL_PATH_BIN "bin/")

  set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror")
  set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} -O0 -ggdb3")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

endif()

add_subdirectory("./core")

add_subdirectory("./simpleapi")

if(PROMETHEUS_BUILD_EXAMPLES)
  add_subdirectory("./examples")
endif()


