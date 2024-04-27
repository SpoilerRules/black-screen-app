cmake_minimum_required(VERSION 3.28)
project(black_screen_app)

set(CMAKE_CXX_STANDARD 23)

# defaults to x86 (Win32) if platform is not specified
if(NOT CMAKE_GENERATOR_PLATFORM)
    set(CMAKE_GENERATOR_PLATFORM "Win32")
endif()

if (MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /Ob2 /Oi /Ot /Oy /GL /GS-")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG")
endif()

set(SOURCES
        src/app/main.cpp
        src/app/WindowInitiator.cpp
        src/app/WindowInitiator.hpp
        src/app/ColorHandler.cpp
        src/app/ColorHandler.hpp
)

if(CMAKE_GENERATOR_PLATFORM STREQUAL "Win32") # Windows x86
    set(EXECUTABLE_NAME "black_screen_app_x86")
elseif(CMAKE_GENERATOR_PLATFORM STREQUAL "x64")
    set(EXECUTABLE_NAME "black_screen_app_x64")
else()
    message(FATAL_ERROR "Unsupported platform: ${CMAKE_GENERATOR_PLATFORM}. Supported platforms are x86 and x64.")
endif()

add_executable(${EXECUTABLE_NAME} WIN32 ${SOURCES})
set_target_properties(${EXECUTABLE_NAME} PROPERTIES OUTPUT_NAME "${EXECUTABLE_NAME}$<$<CONFIG:Debug>:-debug>")
