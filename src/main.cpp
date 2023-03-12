#include <ark/opengl_program.hpp>

class arkanoid : public ark::opengl_program {

    void loop() override {

    }
};

int main() {
    arkanoid game;
    game.start();
    return 0;
}
