cmake_minimum_required( VERSION 3.10 )

add_library(functions STATIC func.cpp)

target_include_directories(functions PUBLIC include)
