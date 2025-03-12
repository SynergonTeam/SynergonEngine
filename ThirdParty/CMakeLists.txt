cmake_minimum_required(VERSION 3.20)

project(SynergonEngineThirdParty)

find_package(glfw3 CONFIG REQUIRED)
find_package(Vulkan REQUIRED)
find_package(GTest CONFIG REQUIRED)

file(GLOB_RECURSE SYNERGON_ENGINE_THIRD_PARTY_INCLUDE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/*.h
)
file(GLOB_RECURSE SYNERGON_ENGINE_THIRD_PARTY_SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES
    ${SYNERGON_ENGINE_THIRD_PARTY_INCLUDE_FILES}
    ${SYNERGON_ENGINE_THIRD_PARTY_SOURCE_FILES}
)

add_library(SynergonEngineThirdParty STATIC
    ${SYNERGON_ENGINE_THIRD_PARTY_INCLUDE_FILES}
    ${SYNERGON_ENGINE_THIRD_PARTY_SOURCE_FILES}
)
add_library(SynergonEngine::ThirdParty ALIAS SynergonEngineThirdParty)

target_include_directories(SynergonEngineThirdParty PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Include
)

target_link_libraries(SynergonEngineThirdParty PUBLIC
    glfw
    Vulkan::Vulkan
    GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main
)

set_property(TARGET SynergonEngineThirdParty PROPERTY FOLDER "Engine")