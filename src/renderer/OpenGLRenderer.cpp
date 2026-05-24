#include "renderer/OpenGLRenderer.h"
#include <GL/glew.h>
#include <spdlog/spdlog.h>
#include <stdexcept>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

static void ortho(float* m, float l, float r, float b, float t) {
    m[ 0]=2/(r-l); m[ 1]=0;       m[ 2]=0;  m[ 3]=0;
    m[ 4]=0;       m[ 5]=2/(t-b); m[ 6]=0;  m[ 7]=0;
    m[ 8]=0;       m[ 9]=0;       m[10]=-1; m[11]=0;
    m[12]=-(r+l)/(r-l); m[13]=-(t+b)/(t-b); m[14]=0; m[15]=1;
}

OpenGLRenderer::OpenGLRenderer(int largura, int altura) {
    _shader.compilar("assets/shaders/sprite.vert",
                     "assets/shaders/sprite.frag");
    _shader.usar();

    _batch.inicializar(
        _shader.uniformLoc("uProjection"),
        _shader.uniformLoc("uAlpha"),
        _shader.uniformLoc("uTextura"));

    recalcularProjecao(largura, altura);

    // textura branca 1×1 para drawRect
    unsigned char branco[4] = {255, 255, 255, 255};
    glGenTextures(1, &_texturaBranca);
    glBindTexture(GL_TEXTURE_2D, _texturaBranca);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, branco);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

OpenGLRenderer::~OpenGLRenderer() {
    if (_texturaBranca) glDeleteTextures(1, &_texturaBranca);
}

void OpenGLRenderer::recalcularProjecao(int w, int h) {
    ortho(_proj, 0.0f, (float)w, (float)h, 0.0f);
    _shader.usar();
    _batch.setProjection(_proj);
}

void OpenGLRenderer::beginFrame(Color c) {
    glClearColor(c.r / 255.0f, c.g / 255.0f, c.b / 255.0f, c.a / 255.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    _shader.usar();
    _batch.setGlobalAlpha(1.0f);
}

void OpenGLRenderer::endFrame() {
    _batch.flush();
}

void OpenGLRenderer::drawTexture(TextureHandle tex, Rect dst, Rect src) {
    Rect uvs = (src.w > 0 && src.h > 0) ? src : Rect{0, 0, 1, 1};
    _batch.adicionarQuad(tex, dst, uvs, Color::white());
}

void OpenGLRenderer::drawRect(Rect r, Color cor) {
    _batch.adicionarQuad(_texturaBranca, r, {0, 0, 1, 1}, cor);
}

void OpenGLRenderer::setGlobalAlpha(float alpha) {
    _batch.flush();
    _batch.setGlobalAlpha(alpha);
}

TextureHandle OpenGLRenderer::loadTexture(const std::string& path) {
    int w, h, ch;
    stbi_set_flip_vertically_on_load(false);
    unsigned char* data = stbi_load(path.c_str(), &w, &h, &ch, 4);
    if (!data) {
        spdlog::warn("loadTexture falhou: {}", path);
        return 0;
    }
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    stbi_image_free(data);
    spdlog::debug("Textura carregada: {} ({}x{})", path, w, h);
    return (TextureHandle)tex;
}

void OpenGLRenderer::freeTexture(TextureHandle tex) {
    GLuint t = (GLuint)tex;
    if (t) glDeleteTextures(1, &t);
}
