cmake_minimum_required(VERSION 3.8)
project(cellphone_password)

set(CMAKE_CXX_STANDARD 17)

set(LIB_HEADERS include/password_node.hpp include/password_space.hpp include/constexpr_utils/utils.hpp include/constexpr_utils/stack.hpp)

add_executable(cellphone_password main.cpp ${LIB_HEADERS})

target_compile_options(cellphone_password PUBLIC
        #-fconstexpr-steps=2147483647
        #-fconstexpr-depth=100
        #-fconstexpr-backtrace-limit=0
        -O3 -Werror -Wall -Wextra)

target_include_directories(cellphone_password PUBLIC include)

option(PRINT_RESULTS "Display all results on stdout" OFF)
option(COMP_TIME_EVAL "Computes the results at compile-time" OFF)

set(DEFINITIONS "")

if (COMP_TIME_EVAL)
    set(DEFINITIONS ${DEFINITIONS} -DCOMPILE_TIME_EVAL=1)
endif()
if (PRINT_RESULTS)
    set(DEFINITIONS ${DEFINITIONS} -DPRINT_RESULT=1)
endif()
target_compile_definitions(cellphone_password PUBLIC ${DEFINITIONS})