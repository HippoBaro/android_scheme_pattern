cmake_minimum_required(VERSION 3.8)
project(cellphone_password)

set(CMAKE_CXX_STANDARD 17)

set(LIB_HEADERS lib/include/password_node.hpp lib/include/password_space.hpp lib/include/constexpr_utils/utils.hpp)

add_executable(cellphone_password main.cpp ${LIB_HEADERS})

target_compile_options(cellphone_password PUBLIC
        -fconstexpr-steps=2147483647
        -fconstexpr-depth=100
        -fconstexpr-backtrace-limit=0
        -O3 -Werror -Wall -Wextra)

target_include_directories(cellphone_password PUBLIC lib/include)

option(DisplayResult "Display results on stdout" ON)
option(CompileTimeEvaluation "Computes the results at compile-time" OFF)

set(DEFINITIONS "")

if (CompileTimeEvaluation)
    set(DEFINITIONS ${DEFINITIONS} -DCOMPILE_TIME_EVAL=1)
endif()
if (DisplayResult)
    set(DEFINITIONS ${DEFINITIONS} -DPRINT_RESULT=1)
endif()
target_compile_definitions(cellphone_password PUBLIC ${DEFINITIONS})