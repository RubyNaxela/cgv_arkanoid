#include <cstdlib>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <lab/shaderprogram.h>

namespace lab {

    void error_callback(int error, const char* description) {
        std::cerr << "error: " << description << "(code: " << error << ")" << std::endl;
    }

    void initOpenGLProgram(GLFWwindow* window) {
        lab::initShaders();
    }

    void freeOpenGLProgram(GLFWwindow* window) {
        lab::freeShaders();
    }
}

int main() {

    GLFWwindow* window;
    glfwSetErrorCallback(lab::error_callback);

    if (not glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    window = glfwCreateWindow(500, 500, "OpenGL Lab", nullptr, nullptr);

    if (not window) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    lab::initOpenGLProgram(window);

    while (not glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    lab::freeOpenGLProgram(window);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
