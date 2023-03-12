#include <ark/opengl_program.hpp>

void ark::opengl_program::error_callback(int error, const char* description) {
    throw std::runtime_error(std::string(description) + "(code: " + std::to_string(error) + ")");
}

ark::opengl_program::opengl_program() {
    glfwSetErrorCallback(error_callback);
    if (not glfwInit()) throw std::runtime_error("Failed to initialize GLFW");
    window.create();
    if (glewInit() != GLEW_OK) throw std::runtime_error("Failed to initialize GLEW");
    lab::shaders::init();
}

ark::opengl_program::~opengl_program() {
    lab::shaders::dispose();
    glfwDestroyWindow(window);
    glfwTerminate();
}

void ark::opengl_program::start() {
    while (not glfwWindowShouldClose(window)) {
        glfwPollEvents();
        loop();
    }
}
