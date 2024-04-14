cmake_minimum_required(VERSION 3.28)
project(black_screen_app)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_GENERATOR_PLATFORM "Win32")

if (MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /Ob2 /Oi /Ot /Oy /GL /GS-")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG")
endif()

add_executable(black_screen_app WIN32
        src/app/main.cpp
        src/app/WindowInitiator.cpp
        src/app/WindowInitiator.hpp
)
