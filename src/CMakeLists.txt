add_executable(${PROJECT_NAME}
        Emulator.cpp
        components/Memory.cpp
        components/Memory.h
        components/IO.cpp
        components/IO.h
        components/Display.cpp
        components/Display.h
        components/Speaker.cpp
        components/Speaker.h
        components/Keyboard.cpp
        components/Keyboard.h
)
target_include_directories(${PROJECT_NAME}
        PRIVATE ${SDL2_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME}
        PRIVATE Intel8080
        PRIVATE ${SDL2_LIBRARIES}
        PRIVATE SDL2_mixer::SDL2_mixer)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/lib $<TARGET_FILE_DIR:${PROJECT_NAME}>)