cmake_minimum_required(VERSION 3.20)

project(SynergonRpi LANGUAGES CXX VERSION 0.0.1)

file(GLOB_RECURSE SYNERGON_ENGINE_RPI_INCLUDE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/Include/*.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Include/*.h
)

file(GLOB_RECURSE SYNERGON_ENGINE_RPI_SOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/Include/*.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Include/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES
        ${SYNERGON_ENGINE_RPI_INCLUDE_FILES}
        ${SYNERGON_ENGINE_RPI_SOURCE_FILES}
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES
        ${SYNERGON_ENGINE_RPI_INCLUDE_FILES}
        ${SYNERGON_ENGINE_RPI_SOURCE_FILES}
)

if(BUILD_SHARED_LIBS)
    add_library(SynergonRpi SHARED
            ${SYNERGON_ENGINE_RPI_INCLUDE_FILES}
            ${SYNERGON_ENGINE_RPI_SOURCE_FILES}
    )
else()
    add_library(SynergonRpi STATIC
            ${SYNERGON_ENGINE_RPI_INCLUDE_FILES}
            ${SYNERGON_ENGINE_RPI_SOURCE_FILES}
    )
endif()


target_include_directories(SynergonRpi PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Include
)

target_link_libraries(SynergonRpi PRIVATE
        SynergonGfx
)

set_property(TARGET SynergonRpi PROPERTY FOLDER "Engine/Modules")
