cmake_minimum_required(VERSION 3.17)

project(OpenGL)

# glfw
add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)

# glew
add_definitions(-DGLEW_STATIC)
add_subdirectory(lib/glew EXCLUDE_FROM_ALL)

# glm
add_subdirectory(lib/glm EXCLUDE_FROM_ALL)

add_subdirectory(common)
add_subdirectory(Triangles)
add_subdirectory(uniform_variables)