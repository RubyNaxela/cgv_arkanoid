#ifndef LAB_PROJECT_OPENGL_PROGRAM
#define LAB_PROJECT_OPENGL_PROGRAM

#include <stdexcept>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ark/render_window.hpp>
#include <lab/shaderprogram.h>

namespace ark {

    class opengl_program {

        static void error_callback(int error, const char* description);

    protected:

        render_window window;

        virtual void loop() = 0;

    public:

        opengl_program();

        ~opengl_program();

        void start();
    };
}

#endif //LAB_PROJECT_OPENGL_PROGRAM
