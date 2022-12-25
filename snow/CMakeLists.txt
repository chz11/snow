#cmake_minimum_required(VERSION 2.8)

#project(base)

#set(CMAKE_CXX_FLAGS "$ENV(CXXFLAS) -rdynamic -O3 -g -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function")

set(base_SRCS
   log.cpp
   )

add_library(base ${base_SRCS})
target_link_libraries(base pthread)

install(TARGETS base DESTINATION lib)

file(GLOB HEADERS "*.h")
install(FILES log.h DESTINATION include/base)
