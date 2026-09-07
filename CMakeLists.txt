cmake_minimum_required(VERSION 4.4)
project(cpp-opengl)

find_package(OpenGL REQUIRED)

add_executable(Application
  src/Application.cpp
)

add_subdirectory(vendor/glfw-3.5.1)

target_link_libraries(Application PRIVATE 
  glfw
  OpenGL::GL
)
