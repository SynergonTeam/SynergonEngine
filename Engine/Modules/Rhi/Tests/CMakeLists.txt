cmake_minimum_required(VERSION 3.20)

project(SynergonRhiTests LANGUAGES CXX VERSION 0.0.1)

file(GLOB_RECURSE SYNERGON_ENGINE_RHI_TESTS_SOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES
        ${SYNERGON_ENGINE_RHI_TESTS_INCLUDE_FILES}
        ${SYNERGON_ENGINE_RHI_TESTS_SOURCE_FILES}
)

add_executable(SynergonRhiTests
        ${SYNERGON_ENGINE_RHI_TESTS_SOURCE_FILES}
)

target_link_libraries(SynergonRhiTests PRIVATE SynergonRhi)
target_link_libraries(SynergonRhiTests PRIVATE GTest::gtest_main)

set_property(TARGET SynergonRhiTests PROPERTY FOLDER "Engine/Modules/Rhi")
