#pragma once
#include <glad/glad.h>
#include <iostream>

#define ASSERT(x)                                                              \
    do {                                                                       \
        if (!(x))                                                              \
            __builtin_debugtrap();                                             \
    } while (0)

#define GLCall(x)                                                              \
    GLClearError();                                                            \
    x;                                                                         \
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char *function, const char *file, int line);
