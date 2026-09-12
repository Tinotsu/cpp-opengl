cmake_minimum_required(VERSION 4.4)

project(cpp-opengl)

find_package(OpenGL REQUIRED)

add_subdirectory(vendor/glfw-3.5.1)

add_executable(Application
  src/Application.cpp
  src/Shader.cpp
  src/Texture.cpp
  src/IndexBuffer.cpp
  src/VertexBuffer.cpp
  src/VertexArray.cpp
  src/Renderer.cpp
  vendor/glad/src/glad.c
  vendor/stb_image/stb_image.cpp
)

target_include_directories(Application PRIVATE
  vendor/glad/include
  vendor/stb_image
)

target_link_libraries(Application PRIVATE
  glfw
  OpenGL::GL
)
