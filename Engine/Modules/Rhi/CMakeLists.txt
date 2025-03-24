cmake_minimum_required(VERSION 3.20)

project(SynergonRhi LANGUAGES CXX VERSION 0.0.1)

file(GLOB_RECURSE SYNERGON_ENGINE_RHI_INCLUDE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/Include/*.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Include/*.h
)

file(GLOB_RECURSE SYNERGON_ENGINE_RHI_SOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES
        ${SYNERGON_ENGINE_RHI_INCLUDE_FILES}
        ${SYNERGON_ENGINE_RHI_SOURCE_FILES}
)

add_library(SynergonRhi STATIC
        ${SYNERGON_ENGINE_RHI_INCLUDE_FILES}
        ${SYNERGON_ENGINE_RHI_SOURCE_FILES}
)

target_include_directories(SynergonRhi PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Include
		${Vulkan_INCLUDE_DIRS}
)

target_link_libraries(SynergonRhi PUBLIC SynergonCore ${Vulkan_LIBRARIES})

set_property(TARGET SynergonRhi PROPERTY FOLDER "Engine/Modules/Rhi")

add_subdirectory(Tests)
