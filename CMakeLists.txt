cmake_minimum_required(VERSION 3.26)
project(SpaceInvaders
    VERSION 1.0.0 DESCRIPTION "A C++ emulator of the classic arcade machine: Space Invaders!")

set(CMAKE_CXX_STANDARD 20)
set(ROM_FOLDER "assets/roms")
set(SOUND_FOLDER "assets/sound")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_RESOURCE_FILE_README ${CMAKE_CURRENT_SOURCE_DIR}/README.md)
set(CPACK_PACKAGE_INSTALL_DIRECTORY "Space Invaders Emulator")

include(CPack)

include(FetchContent)
FetchContent_Declare(
        Intel8080
        GIT_REPOSITORY "https://github.com/harrow22/Intel8080.git"
)
set(INTEL8080_TESTS OFF)
message(STATUS "Fetching Intel 8080 core...")
FetchContent_MakeAvailable(Intel8080)
message(STATUS "Fetched Intel 8080 core")

find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)
add_subdirectory(src)

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION bin COMPONENT space_invaders_installer
        LIBRARY DESTINATION lib COMPONENT space_invaders_installer)
install(DIRECTORY DESTINATION ${ROM_FOLDER})
install(DIRECTORY DESTINATION ${SOUND_FOLDER})