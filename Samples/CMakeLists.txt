cmake_minimum_required(VERSION 3.20)

project(SynergonEngineSamples LANGUAGES CXX VERSION 0.1.0)

if(WIN32)
    option(WIN32_RELEASE_MODE_NO_CONSOLE "Release mode for Win32" OFF)
endif()

set(SYNERGON_ENGINE_ASSETS_SOURCE_DIR ${CMAKE_SOURCE_DIR}/Assets)

if(MSVC)
    set(SYNERGON_ENGINE_ASSETS_DESTINATION_DIR ${CMAKE_BINARY_DIR}/$<CONFIG>/Assets)
else()
    set(SYNERGON_ENGINE_ASSETS_DESTINATION_DIR ${CMAKE_BINARY_DIR}/Assets)
endif()

file(COPY_FILE ${CMAKE_SOURCE_DIR}/.clang-format ${CMAKE_BINARY_DIR}/.clang-format)

file(GLOB_RECURSE SYNERGON_ENGINE_SAMPLES_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/*.h
)
file(GLOB_RECURSE SYNERGON_ENGINE_SAMPLES_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES
    ${SYNERGON_ENGINE_SAMPLES_HEADERS}
    ${SYNERGON_ENGINE_SAMPLES_SOURCES}
)

add_executable(SynergonEngineSamples
    ${SYNERGON_ENGINE_SAMPLES_HEADERS}
    ${SYNERGON_ENGINE_SAMPLES_SOURCES}
)

target_include_directories(SynergonEngineSamples PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Include
)

target_link_libraries(SynergonEngineSamples PRIVATE
    SynergonEngine
)

if(WIN32 AND WIN32_RELEASE_MODE_NO_CONSOLE)
    if(MSVC)
        set_target_properties(SynergonEngineSamples PROPERTIES WIN32_EXECUTABLE $<$<CONFIG:Release>:TRUE>)
    elseif(CMAKE_BUILD_TYPE MATCHES Release)
        set_target_properties(SynergonEngineSamples PROPERTIES WIN32_EXECUTABLE TRUE)
    endif()
endif()

if(MSVC)
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT SynergonEngineSamples)
endif()

find_program(SLANGC_EXECUTABLE slangc REQUIRED)

if(NOT SLANGC_EXECUTABLE)
    message(FATAL_ERROR "Slang compiler not found. Install slangc and add it to PATH.")
endif()

file(GLOB_RECURSE SYNERGON_ENGINE_SAMPLES_SHADERS ${SYNERGON_ENGINE_ASSETS_SOURCE_DIR}/Shaders/*.slang)

foreach(SHADER_FILE ${SYNERGON_ENGINE_SAMPLES_SHADERS})
    get_filename_component(FILE_NAME_WE ${SHADER_FILE} NAME_WE)
    get_filename_component(FILE_PATH ${SHADER_FILE} PATH)

    set(SPIRV ${FILE_PATH}/${FILE_NAME_WE}.spv)

    add_custom_command(
        OUTPUT ${SPIRV}
        COMMAND ${SLANGC_EXECUTABLE} -fvk-use-entrypoint-name -I ${SYNERGON_ENGINE_ASSETS_SOURCE_DIR}/Shaders ${SHADER_FILE} -target spirv -o ${SPIRV}
        DEPENDS ${SHADER_FILE}
    )
    list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach()

if(MSVC)
    set(MSVC_COPY_SYNERGON_ENGINE_ASSETS COMMAND
        ${CMAKE_COMMAND} -E copy_directory_if_different ${SYNERGON_ENGINE_ASSETS_SOURCE_DIR} ${CMAKE_BINARY_DIR}/Modules/Editor/Assets)
else()
    set(MSVC_COPY_SYNERGON_ENGINE_ASSETS)
endif()

add_custom_target(SynergonEngineAssets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different ${SYNERGON_ENGINE_ASSETS_SOURCE_DIR} ${SYNERGON_ENGINE_ASSETS_DESTINATION_DIR}
    ${MSVC_COPY_SYNERGON_ENGINE_ASSETS}
    DEPENDS ${SPIRV_BINARY_FILES} ${SYNERGON_ENGINE_ASSETS_SOURCE_DIR}
    COMMENT "Copying '${SYNERGON_ENGINE_ASSETS_SOURCE_DIR}' folder to '${SYNERGON_ENGINE_ASSETS_DESTINATION_DIR}'"
)

add_dependencies(SynergonEngineSamples SynergonEngineAssets)

file(GLOB_RECURSE SYNERGON_ENGINE_ASSETS_FILES ${SYNERGON_ENGINE_ASSETS_SOURCE_DIR}/*)
source_group(TREE ${SYNERGON_ENGINE_ASSETS_SOURCE_DIR} FILES ${SYNERGON_ENGINE_ASSETS_FILES})
target_sources(SynergonEngineAssets PRIVATE ${SYNERGON_ENGINE_ASSETS_FILES})
target_sources(SynergonEngineSamples PRIVATE ${SYNERGON_ENGINE_ASSETS_FILES})