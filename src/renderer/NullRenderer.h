#ifndef MINECIN_RENDERER_NULLRENDERER_H
#define MINECIN_RENDERER_NULLRENDERER_H

#include "IRenderer.h"

// Usado na simulacao evitando renderizar gráficos.
class NullRenderer : public IRenderer {
public:
    void beginFrame(Color) override {}
    void endFrame() override {}
    void drawTexture(TextureHandle, Rect, Rect) override {}
    void drawRect(Rect, Color) override {}
    void drawText(const std::string&, Vect2, float, Color) override {}
    void setGlobalAlpha(float) override {}
    TextureHandle loadTexture(const std::string&) override { return 0; }
    void freeTexture(TextureHandle) override {}
};

#endif // MINECIN_RENDERER_NULLRENDERER_H
