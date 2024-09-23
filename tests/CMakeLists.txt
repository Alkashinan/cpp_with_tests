
cmake_minimum_required(VERSION 3.10)
project(save_test)

find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED)


enable_testing()

add_executable(save_test savetest.cpp)


target_link_libraries(save_test sfml-graphics sfml-audio sfml-window sfml-system)


find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(save_test ${GTEST_LIBRARIES} pthread)


# target_link_libraries(save_test GTest::GTest GTest::Main)

include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(save_test ${SFML_LIBRARIES})

add_test(SavesCorrectData save_test)
add_test(LoadsCorrectData save_test)
add_test(HandlesFileNotFoundError save_test)
add_test(SkipsToChoicesState save_test)
