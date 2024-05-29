# CMakeList.txt: CMake project for opengl-template, include source and define
# project-specific logic here.
#
cmake_minimum_required(VERSION 3.10)

project (opengl-template)

find_package(glm CONFIG REQUIRED)
find_package(glew CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

# Add the source to this project's executable.
add_executable (opengl-template "opengl-template.cpp" "opengl-template.h")

target_link_libraries(opengl-template PRIVATE glm::glm)
target_link_libraries(opengl-template PRIVATE GLEW::GLEW)
target_link_libraries(opengl-template PRIVATE glfw)
target_link_libraries(opengl-template PRIVATE imgui::imgui)

# TODO: Add tests and install targets, if necessary.
