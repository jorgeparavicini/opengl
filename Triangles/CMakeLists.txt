cmake_minimum_required(VERSION 3.17)

set(EXECUTABLE_NAME "triangles")
project(${EXECUTABLE_NAME})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB SRC "src/*.cpp")

add_executable(${EXECUTABLE_NAME} ${SRC})

# Settings
set_property(TARGET ${EXECUTABLE_NAME} PROPERTY CXX_STANDARD 11)
target_compile_options(${EXECUTABLE_NAME} PRIVATE -Wall)

# glfw
target_link_libraries(${EXECUTABLE_NAME} PRIVATE glfw)

# glew
target_link_libraries(${EXECUTABLE_NAME} PRIVATE libglew_static)

# glm
target_link_libraries(${EXECUTABLE_NAME} PRIVATE glm)

# common library
target_link_libraries(${EXECUTABLE_NAME} PRIVATE common)

include_directories(include)

# Post Build Commands
add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/shaders/ $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>/shaders)