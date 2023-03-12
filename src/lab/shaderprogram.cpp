/*
Niniejszy program jest wolnym oprogramowaniem; możesz go
rozprowadzać dalej i / lub modyfikować na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundację Wolnego
Oprogramowania - według wersji 2 tej Licencji lub(według twojego
wyboru) którejś z późniejszych wersji.

Niniejszy program rozpowszechniany jest z nadzieją, iż będzie on
użyteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyślnej
gwarancji PRZYDATNOŚCI HANDLOWEJ albo PRZYDATNOŚCI DO OKREŚLONYCH
ZASTOSOWAŃ.W celu uzyskania bliższych informacji sięgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnością wraz z niniejszym programem otrzymałeś też egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeśli nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/

#include <iostream>
#include <lab/shaderprogram.h>

lab::ShaderProgram* spLambert;
lab::ShaderProgram* spConstant;

namespace lab {
    void initShaders() {
        spLambert = new ShaderProgram("v_lambert.glsl", NULL, "f_lambert.glsl");
        spConstant = new ShaderProgram("v_constant.glsl", NULL, "f_constant.glsl");
    }

    void freeShaders() {
        delete spLambert;
    }

    // Wczytuje plik do tablicy znaków
    char* ShaderProgram::read_file(const char* filename) {
        int filesize;
        FILE* plik;
        char* result;
        plik = fopen(filename, "rb");
        if (plik != nullptr) {
            fseek(plik, 0, SEEK_END);
            filesize = ftell(plik);
            fseek(plik, 0, SEEK_SET);
            result = new char[filesize + 1];
            int readsize = fread(result, 1, filesize, plik);
            result[filesize] = 0;
            fclose(plik);

            return result;
        }
        std::cerr << "File " << filename << " could not be opened" << std::endl;
        return nullptr;
    }

    // Wczytuje i kompiluje shader, a następnie zwraca jego uchwyt
    GLuint ShaderProgram::load_shader(GLenum shaderType, const char* filename) {
        // Wygeneruj uchwyt na shader
        GLuint shader = glCreateShader(shaderType); // shaderType to GL_VERTEX_SHADER, GL_GEOMETRY_SHADER lub GL_FRAGMENT_SHADER
        // Wczytaj plik ze źródłem shadera do tablicy znaków
        const GLchar* shaderSource = read_file(filename);
        // Powiąż źródło z uchwytem shadera
        glShaderSource(shader, 1, &shaderSource, NULL);
        // Skompiluj źródło
        glCompileShader(shader);
        // Usuń źródło shadera z pamięci (nie będzie już potrzebne)
        delete[]shaderSource;

        // Pobierz log błędów kompilacji i wyświetl
        int infologLength = 0;
        int charsWritten = 0;
        char* infoLog;

        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infologLength);

        if (infologLength > 1) {
            infoLog = new char[infologLength];
            glGetShaderInfoLog(shader, infologLength, &charsWritten, infoLog);
            printf("%s\n", infoLog);
            delete[]infoLog;
        }

        return shader;
    }

    ShaderProgram::ShaderProgram(const char* vertex_shader_file, const char* geometry_shader_file, const char* fragment_shader_file) {
        //Wczytaj vertex shader
        printf("Loading vertex shader...\n");
        vertexShader = load_shader(GL_VERTEX_SHADER, vertex_shader_file);

        //Wczytaj geometry shader
        if (geometry_shader_file != NULL) {
            printf("Loading geometry shader...\n");
            geometryShader = load_shader(GL_GEOMETRY_SHADER, geometry_shader_file);
        } else {
            geometryShader = 0;
        }

        //Wczytaj fragment shader
        printf("Loading fragment shader...\n");
        fragmentShader = load_shader(GL_FRAGMENT_SHADER, fragment_shader_file);

        //Wygeneruj uchwyt programu cieniującego
        shaderProgram = glCreateProgram();

        //Podłącz do niego shadery i zlinkuj program
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        if (geometry_shader_file != NULL) glAttachShader(shaderProgram, geometryShader);
        glLinkProgram(shaderProgram);

        //Pobierz log błędów linkowania i wyświetl
        int infologLength = 0;
        int charsWritten = 0;
        char* infoLog;

        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infologLength);

        if (infologLength > 1) {
            infoLog = new char[infologLength];
            glGetProgramInfoLog(shaderProgram, infologLength, &charsWritten, infoLog);
            printf("%s\n", infoLog);
            delete[]infoLog;
        }

        printf("Shader program created \n");
    }

    ShaderProgram::~ShaderProgram() {
        //Odłącz shadery od programu
        glDetachShader(shaderProgram, vertexShader);
        if (geometryShader != 0) glDetachShader(shaderProgram, geometryShader);
        glDetachShader(shaderProgram, fragmentShader);

        //Wykasuj shadery
        glDeleteShader(vertexShader);
        if (geometryShader != 0) glDeleteShader(geometryShader);
        glDeleteShader(fragmentShader);

        //Wykasuj program
        glDeleteProgram(shaderProgram);
    }

    // Włącza używanie programu cieniującego reprezentowanego przez aktualny obiekt
    void ShaderProgram::use() {
        glUseProgram(shaderProgram);
    }

    // Pobiera numer slotu odpowiadającego zmiennej jednorodnej o nazwie variable_name
    GLuint ShaderProgram::u(const char* variable_name) {
        return glGetUniformLocation(shaderProgram, variable_name);
    }

    // Pobiera numer slotu odpowiadającego atrybutowi o nazwie variable_name
    GLuint ShaderProgram::a(const char* variable_name) {
        return glGetAttribLocation(shaderProgram, variable_name);
    }
}