cmake_minimum_required( VERSION 3.10 )

add_library(saves STATIC saves.cpp)

target_include_directories(saves PUBLIC include)
