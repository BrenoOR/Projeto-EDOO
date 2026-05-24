#include "renderer/ShaderProgram.h"
#include <spdlog/spdlog.h>
#include <fstream>
#include <sstream>
#include <stdexcept>

ShaderProgram::~ShaderProgram() {
    if (_id) glDeleteProgram(_id);
}

GLuint ShaderProgram::compilarShader(GLenum tipo, const std::string& caminho) {
    std::ifstream arquivo(caminho);
    if (!arquivo)
        throw std::runtime_error("Shader nao encontrado: " + caminho);

    std::ostringstream ss;
    ss << arquivo.rdbuf();
    std::string src = ss.str();
    const char* ptr = src.c_str();

    GLuint shader = glCreateShader(tipo);
    glShaderSource(shader, 1, &ptr, nullptr);
    glCompileShader(shader);

    GLint ok;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char log[512];
        glGetShaderInfoLog(shader, sizeof(log), nullptr, log);
        glDeleteShader(shader);
        throw std::runtime_error("Erro ao compilar shader " + caminho + ": " + log);
    }
    return shader;
}

void ShaderProgram::compilar(const std::string& vertPath, const std::string& fragPath) {
    GLuint vert = compilarShader(GL_VERTEX_SHADER,   vertPath);
    GLuint frag = compilarShader(GL_FRAGMENT_SHADER, fragPath);

    _id = glCreateProgram();
    glAttachShader(_id, vert);
    glAttachShader(_id, frag);
    glLinkProgram(_id);

    glDeleteShader(vert);
    glDeleteShader(frag);

    GLint ok;
    glGetProgramiv(_id, GL_LINK_STATUS, &ok);
    if (!ok) {
        char log[512];
        glGetProgramInfoLog(_id, sizeof(log), nullptr, log);
        glDeleteProgram(_id);
        _id = 0;
        throw std::runtime_error(std::string("Erro ao linkar programa: ") + log);
    }
    spdlog::info("ShaderProgram compilado: {} / {}", vertPath, fragPath);
}

void ShaderProgram::usar() const {
    glUseProgram(_id);
}

GLint ShaderProgram::uniformLoc(const char* nome) const {
    return glGetUniformLocation(_id, nome);
}
