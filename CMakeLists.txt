#cmake_minimum_required(VERSION 2.8)

#project(base)

#set(CMAKE_CXX_FLAGS "$ENV(CXXFLAS) -rdynamic -O3 -g -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function")

set(LIB_SRCS
   snow/log.cpp
   snow/Times.cpp
   )

add_library(snow SHARED ${LIB_SRCS})
add_executable(log_test test/log_test.cpp)
add_dependencies(log_test snow)
target_link_libraries(log_test snow)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
