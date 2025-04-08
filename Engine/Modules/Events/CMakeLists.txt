cmake_minimum_required(VERSION 3.20)

project(SynergonEvents LANGUAGES CXX VERSION 0.0.1)

file(GLOB_RECURSE SYNERGON_ENGINE_EVENTS_INCLUDE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/Include/*.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Include/*.h
)

file(GLOB_RECURSE SYNERGON_ENGINE_EVENTS_SOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES
        ${SYNERGON_ENGINE_EVENTS_INCLUDE_FILES}
        ${SYNERGON_ENGINE_EVENTS_SOURCE_FILES}
)

add_library(SynergonEvents STATIC
        ${SYNERGON_ENGINE_EVENTS_INCLUDE_FILES}
        ${SYNERGON_ENGINE_EVENTS_SOURCE_FILES}
)

target_include_directories(SynergonEvents PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Include
)

target_link_libraries(SynergonEvents PUBLIC SynergonCore)

set_property(TARGET SynergonEvents PROPERTY FOLDER "Engine/Modules/Events")
