#include <ark/render_window.hpp>

ark::render_window::render_window() : glfw_window(nullptr) {};

void ark::render_window::create() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    if ((glfw_window = glfwCreateWindow(500, 500, "OpenGL Lab", nullptr, nullptr)) == nullptr)
        throw std::runtime_error("Failed to create GLFW window");

    glfwMakeContextCurrent(glfw_window);
    glfwSwapInterval(1);
}

ark::render_window::operator GLFWwindow*() const {
    return glfw_window;
}
