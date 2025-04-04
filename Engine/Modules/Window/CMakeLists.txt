cmake_minimum_required(VERSION 3.20)

project(SynergonEngineWindow LANGUAGES CXX VERSION 0.0.1)

file(GLOB_RECURSE SYNERGON_ENGINE_WINDOW_INCLUDE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/Include/*.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Include/*.h
)
file(GLOB_RECURSE SYNERGON_ENGINE_WINDOW_SOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES
        ${SYNERGON_ENGINE_WINDOW_INCLUDE_FILES}
        ${SYNERGON_ENGINE_WINDOW_SOURCE_FILES}
)

if(BUILD_SHARED_LIBS)
    add_library(SynergonWindow SHARED
            ${SYNERGON_ENGINE_WINDOW_INCLUDE_FILES}
            ${SYNERGON_ENGINE_WINDOW_SOURCE_FILES}
    )
else()
    add_library(SynergonWindow STATIC
            ${SYNERGON_ENGINE_WINDOW_INCLUDE_FILES}
            ${SYNERGON_ENGINE_WINDOW_SOURCE_FILES}
    )
endif()

target_include_directories(SynergonWindow PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Include
)

target_link_libraries(SynergonWindow PUBLIC glfw)

set_property(TARGET SynergonWindow PROPERTY FOLDER "Engine/Modules/Window")

add_subdirectory(Tests)