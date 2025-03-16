cmake_minimum_required(VERSION 3.20)

project(SynergonEngineCore LANGUAGES CXX VERSION 0.0.1)

file(GLOB_RECURSE SYNERGON_ENGINE_CORE_INCLUDE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/Include/*.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Include/*.h
)
file(GLOB_RECURSE SYNERGON_ENGINE_CORE_SOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES
        ${SYNERGON_ENGINE_CORE_INCLUDE_FILES}
        ${SYNERGON_ENGINE_CORE_SOURCE_FILES}
)

if(BUILD_SHARED_LIBS)
    add_library(SynergonCore SHARED
            ${SYNERGON_ENGINE_CORE_INCLUDE_FILES}
            ${SYNERGON_ENGINE_CORE_SOURCE_FILES}
    )
else()
    add_library(SynergonCore STATIC
            ${SYNERGON_ENGINE_CORE_INCLUDE_FILES}
            ${SYNERGON_ENGINE_CORE_SOURCE_FILES}
    )
endif()


target_include_directories(SynergonCore PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Include
)

set_property(TARGET SynergonCore PROPERTY FOLDER "Engine/Modules")
