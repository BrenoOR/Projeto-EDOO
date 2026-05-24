#ifndef MINECIN_RENDERER_SHADERPROGRAM_H
#define MINECIN_RENDERER_SHADERPROGRAM_H

#include <GL/glew.h>
#include <string>

class ShaderProgram {
    GLuint _id = 0;
public:
    ShaderProgram() = default;
    ~ShaderProgram();

    ShaderProgram(const ShaderProgram&)            = delete;
    ShaderProgram& operator=(const ShaderProgram&) = delete;

    void compilar(const std::string& vertPath, const std::string& fragPath);
    void usar() const;

    GLint uniformLoc(const char* nome) const;
    GLuint id() const { return _id; }

private:
    static GLuint compilarShader(GLenum tipo, const std::string& caminho);
};

#endif // MINECIN_RENDERER_SHADERPROGRAM_H
