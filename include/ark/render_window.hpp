#ifndef LAB_PROJECT_RENDER_WINDOW
#define LAB_PROJECT_RENDER_WINDOW

#pragma clang diagnostic push
#pragma ide diagnostic ignored "google-explicit-constructor"

#include <stdexcept>
#include <GLFW/glfw3.h>

namespace ark {

    class render_window {

        GLFWwindow* glfw_window;

    public:

        render_window();

        void create();

        operator GLFWwindow*() const;
    };
}

#pragma clang diagnostic pop

#endif //LAB_PROJECT_RENDER_WINDOW
