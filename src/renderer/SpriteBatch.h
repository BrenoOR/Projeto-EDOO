#ifndef MINECIN_RENDERER_SPRITEBATCH_H
#define MINECIN_RENDERER_SPRITEBATCH_H

#include <GL/glew.h>
#include "tipos/Rect.h"
#include "tipos/Color.h"
#include "renderer/IRenderer.h"
#include <vector>

struct Vertice {
    float x, y;
    float u, v;
    float r, g, b, a;
};

class SpriteBatch {
    static constexpr int MAX_QUADS = 8192;

    GLuint _vao = 0, _vbo = 0;
    std::vector<Vertice> _buffer;
    TextureHandle        _texAtual  = 0;
    GLint                _locProj   = -1;
    GLint                _locAlpha  = -1;
    GLint                _locTex    = -1;

public:
    SpriteBatch() = default;
    ~SpriteBatch();

    SpriteBatch(const SpriteBatch&)            = delete;
    SpriteBatch& operator=(const SpriteBatch&) = delete;

    void inicializar(GLint locProj, GLint locAlpha, GLint locTex);
    void setProjection(const float* mat4);
    void setGlobalAlpha(float alpha);

    void adicionarQuad(TextureHandle tex, Rect dst, Rect src, Color cor);
    void flush();
    void limpar();

private:
    float _alpha = 1.0f;
};

#endif // MINECIN_RENDERER_SPRITEBATCH_H
