cmake_minimum_required(VERSION 3.20)

add_subdirectory(ThirdParty)
add_subdirectory(Engine)

if(NOT WITHOUT_SAMPLES)
    add_subdirectory(Application)
endif()