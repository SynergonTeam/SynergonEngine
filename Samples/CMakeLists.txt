cmake_minimum_required(VERSION 3.20)

project(SynergonEngineSamples LANGUAGES CXX VERSION 0.1.0)

if(WIN32)
    option(WIN32_RELEASE_MODE_NO_CONSOLE "Release mode for Win32" OFF)
endif()

set(SYNERGON_ENGINE_ASSETS_SOURCE_DIR ${CMAKE_SOURCE_DIR}/Assets)

# Where we want the final Assets folder to appear in the build folder
set(SYNERGON_ENGINE_ASSETS_DESTINATION_DIR ${CMAKE_BINARY_DIR}/Assets)

# New variable for compiled-shader build outputs:
set(SYNERGON_ENGINE_SHADER_BUILD_DIR ${SYNERGON_ENGINE_ASSETS_DESTINATION_DIR}/Shaders)

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

# Grab all .slang shaders from the source assets directory
file(GLOB_RECURSE SYNERGON_ENGINE_SAMPLES_SHADERS
        ${SYNERGON_ENGINE_ASSETS_SOURCE_DIR}/Shaders/*.slang
)

set(SPIRV_BINARY_FILES "")
set(DXIL_BINARY_FILES "")

foreach(SHADER_FILE ${SYNERGON_ENGINE_SAMPLES_SHADERS})
    get_filename_component(FILE_NAME_WE ${SHADER_FILE} NAME_WE)

    # Direct outputs to the build folder
    set(SPIRV ${SYNERGON_ENGINE_SHADER_BUILD_DIR}/${FILE_NAME_WE}.spv)
    set(VS_DXIL ${SYNERGON_ENGINE_SHADER_BUILD_DIR}/${FILE_NAME_WE}.vs.dxil)
    set(FS_DXIL ${SYNERGON_ENGINE_SHADER_BUILD_DIR}/${FILE_NAME_WE}.fs.dxil)

    # Compile SPIR-V
    add_custom_command(
            OUTPUT ${SPIRV}
            COMMAND ${SLANGC_EXECUTABLE}
            -fvk-use-entrypoint-name
            -I ${SYNERGON_ENGINE_ASSETS_SOURCE_DIR}
            ${SHADER_FILE}
            -target spirv
            -o ${SPIRV}
            DEPENDS ${SHADER_FILE}
    )
    list(APPEND SPIRV_BINARY_FILES ${SPIRV})

    # Compile vertex shader to DXIL
    add_custom_command(
            OUTPUT ${VS_DXIL}
            COMMAND ${SLANGC_EXECUTABLE}
            -I ${SYNERGON_ENGINE_ASSETS_SOURCE_DIR}
            ${SHADER_FILE}
            -target dxil
            -profile sm_6_3
            -entry vsmain
            -o ${VS_DXIL}
            DEPENDS ${SHADER_FILE}
    )

    # Compile fragment shader to DXIL
    add_custom_command(
            OUTPUT ${FS_DXIL}
            COMMAND ${SLANGC_EXECUTABLE}
            -I ${SYNERGON_ENGINE_ASSETS_SOURCE_DIR}
            ${SHADER_FILE}
            -target dxil
            -profile sm_6_3
            -entry fsmain
            -o ${FS_DXIL}
            DEPENDS ${SHADER_FILE}
    )

    list(APPEND DXIL_BINARY_FILES ${VS_DXIL} ${FS_DXIL})
endforeach()

# Copy all assets (including any precompiled assets) into the build folder
add_custom_target(SynergonEngineAssets ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
        ${SYNERGON_ENGINE_ASSETS_SOURCE_DIR}
        ${SYNERGON_ENGINE_ASSETS_DESTINATION_DIR}
        DEPENDS
        ${SPIRV_BINARY_FILES}
        ${DXIL_BINARY_FILES}
        ${SYNERGON_ENGINE_ASSETS_SOURCE_DIR}
        COMMENT "Copying '${SYNERGON_ENGINE_ASSETS_SOURCE_DIR}' folder to '${SYNERGON_ENGINE_ASSETS_DESTINATION_DIR}'"
)

# Make sure the SynergonEngineSamples build depends on the custom assets build
add_dependencies(SynergonEngineSamples SynergonEngineAssets)

# For IDEs: group the asset files nicely under "Assets" in the project tree
file(GLOB_RECURSE SYNERGON_ENGINE_ASSETS_FILES ${SYNERGON_ENGINE_ASSETS_SOURCE_DIR}/*)
source_group(TREE ${SYNERGON_ENGINE_ASSETS_SOURCE_DIR} PREFIX Assets FILES ${SYNERGON_ENGINE_ASSETS_FILES})
target_sources(SynergonEngineAssets PRIVATE ${SYNERGON_ENGINE_ASSETS_FILES})

set_property(TARGET SynergonEngineAssets PROPERTY FOLDER "Samples")
set_property(TARGET SynergonEngineSamples PROPERTY FOLDER "Samples")
