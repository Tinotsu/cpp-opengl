#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "IndexBuffer.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

int main(void) {
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // required on macOS

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    glClearColor(1.0f, 0.5f, 0.5f, 1.0f);

    float positions[] = {
        -0.5f, -0.5f, 0.0F, 0.0f, // 0
        0.5f,  -0.5f, 1.0f, 0.0f, // 1
        0.5f,  0.5f,  1.0,  1.0f, // 2
        -0.5f, 0.5f,  0.0f, 1.0f  // 3
    };

    // Index Buffer = transform any form into a triangle
    unsigned int indices[] = {
        0, 1, 2, //
        2, 3, 0  //
    };

    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCall(glEnable(GL_BLEND));

    VertexArray va;

    /* Create and fill the VBO (=Vertex Buffer Object), stores the actual vertex
     * data */
    VertexBuffer vb(positions, 4 * 4 * sizeof(float));

    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);

    /* Index Buffer Object, abstraction to reuse vertex data */
    IndexBuffer ib(indices, 6);

    glm::mat4 proj = glm::ortho(-4.0f, 4.0f, -3.0f, 3.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-2, 0, 0));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(2, 2, 0));

    glm::mat4 mvp = proj * view * model;

    Shader shader("./res/shaders/Basic.shader");
    shader.Bind();
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind the current buffer
    shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
    shader.SetUniformMat4f("u_MVP", mvp);

    Texture texture("res/textures/capsule_corp.jpeg");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);

    va.UnBind();
    vb.UnBind();
    ib.UnBind();
    shader.UnBind();

    Renderer renderer;

    float r = 0.0f;
    float increment = 0.05;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        renderer.Clear();

        shader.Bind();
        shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

        renderer.Draw(va, ib, shader);

        if (r > 1.0f) {
            increment = -0.05f;
        } else if (r < 0.0f) {
            increment = 0.05f;
        }

        r += increment;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
