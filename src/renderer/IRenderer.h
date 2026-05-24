#ifndef MINECIN_RENDERER_IRENDERER_H
#define MINECIN_RENDERER_IRENDERER_H

#include <string>
#include <cstdint>
#include "tipos/Rect.h"
#include "tipos/Vect2.h"
#include "tipos/Color.h"

using TextureHandle = uint32_t;

class IRenderer {
public:
    virtual ~IRenderer() = default;

    virtual void beginFrame(Color clearColor) = 0;
    virtual void endFrame() = 0;
    virtual void drawTexture(TextureHandle tex, Rect dst, Rect src = {}) = 0;
    virtual void drawRect(Rect r, Color color) = 0;
    virtual void drawText(const std::string& text, Vect2 pos, float scale, Color color) = 0;
    virtual void setGlobalAlpha(float alpha) = 0;
    virtual TextureHandle loadTexture(const std::string& path) = 0;
    virtual void freeTexture(TextureHandle tex) = 0;
};

#endif // MINECIN_RENDERER_IRENDERER_H
