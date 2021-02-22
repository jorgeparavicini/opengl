#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "common/LoadShaders.h"

#define BUFFER_OFFSET(a) ((void*)(a))

enum VAO_IDS {
    Triangles, NumVAOs
};
enum Buffer_IDs {
    ArrayBuffer, NumBuffers
};
enum Attrib_IDs {
    vPosition = 0
};

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

const GLuint NumVertices = 6;

void init() {
    glCreateVertexArrays(NumVAOs, VAOs);
    glBindVertexArray(VAOs[Triangles]);

    GLfloat vertices[NumVertices][2] = {
            //Triangle 1
            {-0.90f, -0.90f},
            {0.85f,  -0.90f},
            {-0.90f, 0.85f},

            // Triangle 2
            {0.90f,  -0.85f},
            {0.90f,  0.90f},
            {-0.85f, 0.90f}
    };
    
    glCreateBuffers(NumBuffers, Buffers);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
    glBufferStorage(GL_ARRAY_BUFFER, sizeof(vertices), vertices, 0);

    ShaderInfo shaders[] = {
            {GL_VERTEX_SHADER,   "shaders/triangles.vert"},
            {GL_FRAGMENT_SHADER, "shaders/triangles.frag"},
            {GL_NONE,            nullptr}
    };

    GLuint program = LoadShaders(shaders);
    glUseProgram(program);

    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(vPosition);
}

void display() {
    static const float black[] = {0.0f, 0.0f, 0.0f, 0.0f};

    glClearBufferfv(GL_COLOR, 0, black);
    glBindVertexArray(VAOs[Triangles]);
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);
}

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                const GLchar *message, const void *userParam) {
    std::cerr << "Gl CALLBACK: " << (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "") << " type = 0x" << type
              << ", severity = 0x" << severity << ", message = " << message << std::endl;
}

int main(int argc, char **argv) {
    glfwInit();

    GLFWwindow *window = glfwCreateWindow(800, 600, "Triangles", nullptr, nullptr);

    glfwMakeContextCurrent(window);
    glewInit();

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, nullptr);

    init();

    while (!glfwWindowShouldClose(window)) {
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

