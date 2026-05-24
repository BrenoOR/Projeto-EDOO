#include "renderer/SpriteBatch.h"
#include <cstring>

SpriteBatch::~SpriteBatch() {
    if (_vbo) glDeleteBuffers(1, &_vbo);
    if (_vao) glDeleteVertexArrays(1, &_vao);
}

void SpriteBatch::inicializar(GLint locProj, GLint locAlpha, GLint locTex) {
    _locProj  = locProj;
    _locAlpha = locAlpha;
    _locTex   = locTex;
    _buffer.reserve(MAX_QUADS * 6);

    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 MAX_QUADS * 6 * sizeof(Vertice),
                 nullptr, GL_DYNAMIC_DRAW);

    // aPos
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertice),
                          (void*)offsetof(Vertice, x));
    // aUV
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertice),
                          (void*)offsetof(Vertice, u));
    // aColor
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertice),
                          (void*)offsetof(Vertice, r));

    glBindVertexArray(0);
}

void SpriteBatch::setProjection(const float* mat4) {
    glUniformMatrix4fv(_locProj, 1, GL_FALSE, mat4);
}

void SpriteBatch::setGlobalAlpha(float alpha) {
    _alpha = alpha;
}

void SpriteBatch::adicionarQuad(TextureHandle tex, Rect dst, Rect src, Color cor) {
    if (!_buffer.empty() &&
        (tex != _texAtual || (int)_buffer.size() >= MAX_QUADS * 6))
        flush();
    _texAtual = tex;

    float x0 = dst.x,           y0 = dst.y;
    float x1 = dst.x + dst.w,   y1 = dst.y + dst.h;
    float u0 = src.x,            v0 = src.y;
    float u1 = src.x + src.w,   v1 = src.y + src.h;
    float r = cor.r / 255.0f, g = cor.g / 255.0f,
          b = cor.b / 255.0f, a = cor.a / 255.0f;

    // dois triângulos formando o quad
    _buffer.push_back({x0, y0, u0, v0, r, g, b, a});
    _buffer.push_back({x1, y0, u1, v0, r, g, b, a});
    _buffer.push_back({x1, y1, u1, v1, r, g, b, a});

    _buffer.push_back({x0, y0, u0, v0, r, g, b, a});
    _buffer.push_back({x1, y1, u1, v1, r, g, b, a});
    _buffer.push_back({x0, y1, u0, v1, r, g, b, a});
}

void SpriteBatch::flush() {
    if (_buffer.empty()) return;

    glUniform1f(_locAlpha, _alpha);
    glUniform1i(_locTex, 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texAtual);

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0,
                    _buffer.size() * sizeof(Vertice),
                    _buffer.data());
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)_buffer.size());
    glBindVertexArray(0);

    _buffer.clear();
}

void SpriteBatch::limpar() {
    _buffer.clear();
    _texAtual = 0;
}
