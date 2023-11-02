cmake_minimum_required(VERSION 3.26)
project(SpaceInvaders)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        Intel8080
        INTEL8080_TESTS OFF
        GIT_REPOSITORY "https://github.com/harrow22/Intel8080.git"
)
message(STATUS "Fetching Intel 8080 core...")
FetchContent_MakeAvailable(Intel8080)
message(STATUS "Fetched Intel 8080 core")

find_package(SDL2 REQUIRED)
set(AUTO_FETCH_SDL2 OFF)
set(SDL2_FETCHED OFF)

if(NOT SDL2_FOUND AND AUTO_FETCH_SDL2)
    FetchContent_Declare(
            SDL
            GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
            GIT_TAG release-2.28.4
            GIT_SHALLOW TRUE
            GIT_PROGRESS TRUE
    )
    message(STATUS "Fetching SDL2...")
    FetchContent_MakeAvailable(SDL)
    set_property(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/_deps/sdl-src" PROPERTY EXCLUDE_FROM_ALL TRUE)

    message(STATUS "Fetched SDL2")
    set(SDL2_FETCHED ON)
endif()

if (SDL2_FOUND OR SDL2_FETCHED)
    add_subdirectory(src)
else()
    message(FATAL_ERROR "SDL2 dependency not available. If you have SDL2 installed rerun with -DCMAKE_PREFIX_PATH=<path/to/sdl2> specified. Otherwise you can run with AUTO_FETCH_SDL2=ON to automatically download the SDL2 source.")
endif()