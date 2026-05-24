#ifndef MINECIN_RENDERER_OPENGLRENDERER_H
#define MINECIN_RENDERER_OPENGLRENDERER_H

#include "renderer/IRenderer.h"
#include "renderer/ShaderProgram.h"
#include "renderer/SpriteBatch.h"
#include "tipos/Color.h"

class OpenGLRenderer : public IRenderer {
    ShaderProgram _shader;
    SpriteBatch   _batch;
    TextureHandle _texturaBranca = 0;

    float _proj[16]{};

    void recalcularProjecao(int w, int h);

public:
    OpenGLRenderer(int largura, int altura);
    ~OpenGLRenderer() override;

    void beginFrame(Color clearColor) override;
    void endFrame()                   override;

    void drawTexture(TextureHandle tex, Rect dst, Rect src) override;
    void drawRect(Rect r, Color color)                      override;
    void drawText(const std::string&, Vect2, float, Color)  override {}

    void setGlobalAlpha(float alpha) override;

    TextureHandle loadTexture(const std::string& path) override;
    void freeTexture(TextureHandle tex)                override;
};

#endif // MINECIN_RENDERER_OPENGLRENDERER_H
