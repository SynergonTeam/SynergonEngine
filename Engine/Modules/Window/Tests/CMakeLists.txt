cmake_minimum_required(VERSION 3.20)

project(SynergonWindowTests LANGUAGES CXX VERSION 0.0.1)

file(GLOB_RECURSE SYNERGON_ENGINE_WINDOW_TESTS_SOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES
        ${SYNERGON_ENGINE_WINDOW_TESTS_INCLUDE_FILES}
        ${SYNERGON_ENGINE_WINDOW_TESTS_SOURCE_FILES}
)

add_executable(SynergonWindowTests
        ${SYNERGON_ENGINE_WINDOW_TESTS_SOURCE_FILES}
)

target_link_libraries(SynergonWindowTests PRIVATE SynergonWindow)
target_link_libraries(SynergonWindowTests PRIVATE GTest::gtest_main)

set_property(TARGET SynergonWindowTests PROPERTY FOLDER "Engine/Modules/Window")
