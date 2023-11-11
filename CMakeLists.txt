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
find_package(SDL2_mixer REQUIRED)
add_subdirectory(src)