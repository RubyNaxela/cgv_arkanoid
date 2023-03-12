cmake_minimum_required(VERSION 3.24)
project(lab_project)

set(CMAKE_CXX_STANDARD 20)

include_directories(include lib/glfw-3.3.8/include /opt/homebrew/Cellar/glew/2.2.0_1/include)
link_directories(lib/glfw-3.3.8/lib-arm64 /opt/homebrew/Cellar/glew/2.2.0_1/lib)

add_executable(lab_project
        src/main.cpp
        src/ark/opengl_program.cpp
        src/ark/render_window.cpp
        src/lab/shaderprogram.cpp
)

target_link_libraries(lab_project libglfw3.a libGLEW.a "-framework OpenGL" "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")