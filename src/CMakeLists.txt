add_executable(${PROJECT_NAME}
        main.cpp)
target_link_libraries(${PROJECT_NAME}
        PRIVATE ${SDL2_LIBRARIES}
        PRIVATE Intel8080)
target_include_directories(${PROJECT_NAME}
        PRIVATE ${SDL2_INCLUDE_DIR})
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/lib $<TARGET_FILE_DIR:${PROJECT_NAME}>)