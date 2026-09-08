# Project for me to learn OpenGL

## Pipeline

1. We store some data (vertex buffer) in the GPU
2. We execute shaders (=program for GPU) to display those data on the screen

## Vertex Buffer

- Vertices are not position, they are just point with attribute (attribute can contains position thought).
- Vertex Buffer (VBO) : GPU buffer containing vertex attribute data.
- Attribute : information of the vertex like position, colors etc.
- Strides : size of Vertex in bytes.
- Offset/Pointer (in OpenGL) : pointer in the attribute, offset inside GPU buffer storage.

## Shaders

- Program which runs on GPU
- Vertex Shaders : Tell openGL where the vertex will be on the screen -> Provide vertex position.
- Fragment Shaders : Program that is called for each pixels on the screen, process called rasterization stage.

## Index Buffer

Abstraction for reusing vertex data
