#ifndef MINECIN_CORE_GERENCIADORASSETS_H
#define MINECIN_CORE_GERENCIADORASSETS_H

#include <string>
#include "renderer/IRenderer.h"

class GerenciadorAssets {
    IRenderer& _renderer;
public:
    explicit GerenciadorAssets(IRenderer& renderer) : _renderer(renderer) {}

    TextureHandle carregarTextura(const std::string&) { return 0; }
    void liberarTextura(TextureHandle) {}
};

#endif // MINECIN_CORE_GERENCIADORASSETS_H
