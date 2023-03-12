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

lab::ShaderProgram* lab::shaders::spLambert, * lab::shaders::spConstant;

void lab::shaders::init() {
    lab::shaders::spLambert = new lab::ShaderProgram("v_lambert.glsl", nullptr, "f_lambert.glsl");
    lab::shaders::spConstant = new lab::ShaderProgram("v_constant.glsl", nullptr, "f_constant.glsl");
}

void lab::shaders::dispose() {
    delete lab::shaders::spLambert;
    delete lab::shaders::spConstant;
}

char* lab::ShaderProgram::read_file(const char* filename) {
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

GLuint lab::ShaderProgram::load_shader(GLenum shaderType, const char* filename) {
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

lab::ShaderProgram::ShaderProgram(const char* vertex_shader_file, const char* geometry_shader_file,
                                  const char* fragment_shader_file) {
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

lab::ShaderProgram::~ShaderProgram() {
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

void lab::ShaderProgram::use() const {
    glUseProgram(shaderProgram);
}

GLuint lab::ShaderProgram::u(const char* variable_name) const {
    return glGetUniformLocation(shaderProgram, variable_name);
}

GLuint lab::ShaderProgram::a(const char* variable_name) const {
    return glGetAttribLocation(shaderProgram, variable_name);
}