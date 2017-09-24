cmake_minimum_required(VERSION 3.8)
project(cellphone_password)

set(CMAKE_CXX_STANDARD 17)

set(LIB_HEADERS lib/include/password_node.hpp lib/include/password_space.hpp lib/include/constexpr_utils/utils.hpp)

add_executable(cellphone_password main.cpp ${LIB_HEADERS})

target_compile_options(cellphone_password PUBLIC -fconstexpr-steps=2147483647 -fconstexpr-depth=100 -fconstexpr-backtrace-limit=0)
target_include_directories(cellphone_password PUBLIC lib/include)
target_compile_definitions(cellphone_password PUBLIC)
#target_compile_definitions(cellphone_password PUBLIC -DNDEBUG=1)
#target_compile_options(cellphone_password PUBLIC -O3 -Werror -Wall -Wextra)