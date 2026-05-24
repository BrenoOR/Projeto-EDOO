#ifndef MINECIN_CORE_GERENCIADORASSETS_H
#define MINECIN_CORE_GERENCIADORASSETS_H

#include <string>
#include "renderer/IRenderer.h"

class GerenciadorAssets {
    IRenderer& _renderer;
public:
    explicit GerenciadorAssets(IRenderer& renderer) : _renderer(renderer) {}

    TextureHandle carregarTextura(const std::string& path) {
        return _renderer.loadTexture(path);
    }
    void liberarTextura(TextureHandle tex) {
        _renderer.freeTexture(tex);
    }
};

#endif // MINECIN_CORE_GERENCIADORASSETS_H
