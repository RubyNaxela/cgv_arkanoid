/*
Niniejszy program jest wolnym oprogramowaniem; możesz go
rozprowadzać dalej i / lub modyfikować na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundację Wolnego
Oprogramowania - według wersji 2 tej Licencji lub(według twojego
wyboru) którejś z późniejszych wersji.

Niniejszy program rozpowszechniany jest z nadzieją, iż będzie on
użyteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyślnej
gwarancji PRZYDATNOśCI HANDLOWEJ albo PRZYDATNOśCI DO OKREśLONYCH
ZASTOSOWAń.W celu uzyskania bliższych informacji sięgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnością wraz z niniejszym programem otrzymałeś też egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeśli nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/


#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <cstdio>
#include <GL/glew.h>

namespace lab {
    class ShaderProgram {

    private:
        GLuint shaderProgram; //Uchwyt reprezentujący program cieniujacy
        GLuint vertexShader; // Uchwyt reprezentujący vertex shader
        GLuint geometryShader; //Uchwyt reprezentujący geometry shader
        GLuint fragmentShader; //Uchwyt reprezentujący fragment shader

        // Wczytuje plik tekstowy do tablicy znaków
        static char* read_file(const char* filename);

        // Wczytuje i kompiluje shader, a następnie zwraca jego uchwyt
        static GLuint load_shader(GLenum shaderType, const char* filename);

    public:

        ShaderProgram(const char* vertex_shader_file, const char* geometry_shader_file, const char* fragment_shader_file);

        ~ShaderProgram();

        // Włącza wykorzystywanie programu cieniującego
        void use();

        // Pobiera numer slotu związanego z daną zmienną jednorodną
        GLuint u(const char* variable_name);

        // Pobiera numer slotu związanego z danym atrybutem
        GLuint a(const char* variable_name);
    };

    void initShaders();

    void freeShaders();
}

extern lab::ShaderProgram* spConstant;
extern lab::ShaderProgram* spLambert;

#endif
