cmake_minimum_required(VERSION 3.8)
project(cellphone_password)

set(CMAKE_CXX_STANDARD 17)

set(LIB_HEADERS include/password_node.hpp include/password_space.hpp include/constexpr_utils/utils.hpp include/constexpr_utils/stack.hpp)

add_executable(cellphone_password main.cpp ${LIB_HEADERS})

set(OPTS -O3 -Werror -Wall -Wextra)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
    set(OPTS ${OPTS} -fconstexpr-steps=2147483647)
endif()

target_compile_options(cellphone_password PUBLIC ${OPTS})
target_include_directories(cellphone_password PUBLIC include)

option(COMP_TIME_EVAL "Computes the results at compile-time" OFF)
option(PRINT_SCHEMES "Prints all found combinations on stdout" OFF)
option(USE_SYMMETRY "Computes the results using symmetry (reduces computational cost)" ON)

set(DEFINITIONS "")
if (COMP_TIME_EVAL AND PRINT_SCHEMES)
    message(FATAL_ERROR "COMP_TIME_EVAL & PRINT_SCHEMES cannot be used at the same time." )
endif()
if (USE_SYMMETRY AND PRINT_SCHEMES)
    message(WARNING "When using USE_SYMMETRY, every schemes won't be outputted." )
endif()

if (COMP_TIME_EVAL)
    set(DEFINITIONS ${DEFINITIONS} -DCOMPILE_TIME_EVAL=1)
endif()
if (PRINT_SCHEMES)
    set(DEFINITIONS ${DEFINITIONS} -DPRINT_RESULT=1)
endif()
if (USE_SYMMETRY)
    set(DEFINITIONS ${DEFINITIONS} -DUSE_SYMMETRY=1)
endif()
target_compile_definitions(cellphone_password PUBLIC ${DEFINITIONS})

find_package (Threads)
target_link_libraries(cellphone_password PUBLIC ${CMAKE_THREAD_LIBS_INIT})