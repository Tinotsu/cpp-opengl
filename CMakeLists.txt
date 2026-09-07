cmake_minimum_required(VERSION 4.4)

project(cpp-opengl)

find_package(OpenGL REQUIRED)

add_subdirectory(vendor/glfw-3.5.1)

add_executable(Application
  src/Application.cpp
  vendor/glad/src/glad.c
)

target_include_directories(Application PRIVATE
  vendor/glad/include
)

target_link_libraries(Application PRIVATE
  glfw
  OpenGL::GL
)
