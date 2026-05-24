#ifndef MINECIN_CORE_ASSETSHANDLER_H
#define MINECIN_CORE_ASSETSHANDLER_H

#include "renderer/IRenderer.h"
#include <string>

struct CacheSprites {
    TextureHandle pedra     = 0;
    TextureHandle magnetita = 0;
    TextureHandle cobre     = 0;
    TextureHandle ouro      = 0;
    TextureHandle muro      = 0;
    TextureHandle overlay   = 0;
    TextureHandle robo[2][4][2]{};
    // ícones do HUD
    TextureHandle icone_magnetita = 0;
    TextureHandle icone_cobre     = 0;
    TextureHandle icone_ouro      = 0;
    TextureHandle icone_pedra     = 0;
};

class AssetsHandler {
    IRenderer&   _renderer;
    CacheSprites _sprites;
public:
    explicit AssetsHandler(IRenderer& renderer) : _renderer(renderer) {}

    void carregarTodos();
    void carregarIcones();

    TextureHandle carregarTextura(const std::string& path) {
        return _renderer.loadTexture(path);
    }
    void liberarTextura(TextureHandle tex) {
        _renderer.freeTexture(tex);
    }

    const CacheSprites& sprites() const { return _sprites; }
};

#endif // MINECIN_CORE_ASSETSHANDLER_H
