
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O3 -fPIC -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined -Wno-deprecated-declarations")
set(base_SRCS
   ../log.cpp
   ../Times.cpp
   )

add_library(base SHARED ${base_SRCS})
add_executable(log_test log_test.cpp)
add_dependencies(log_test base)
target_link_libraries(log_test base)
set(EXECUTABLE_OUTPUT_PATH $(PROJECT_SOURCE_DIR)/bin)
set(LIBRARY_OUTPUT_PATH $(PROJECT_SOURCE_DIR)/lib)