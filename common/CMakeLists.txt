cmake_minimum_required(VERSION 3.17)

set(COMMON_LIBRARY "common")
project(${COMMON_LIBRARY})

file(GLOB SRC "src/*.cpp")

include_directories(include)
add_library(${COMMON_LIBRARY} ${SRC} ../uniform_variables/src/main.cpp)

target_include_directories(${COMMON_LIBRARY} INTERFACE include)

# glfw
target_link_libraries(${COMMON_LIBRARY} PRIVATE glfw)

# glew
target_link_libraries(${COMMON_LIBRARY} PRIVATE libglew_static)

# glm
target_link_libraries(${COMMON_LIBRARY} PRIVATE glm)