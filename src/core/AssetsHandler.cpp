#include "core/AssetsHandler.h"

static const char* FACING_NOMES[4] = {"cima", "baixo", "esquerda", "direita"};

void AssetsHandler::carregarTodos() {
    _sprites.pedra     = carregarTextura("assets/sprites/pedra.png");
    _sprites.magnetita = carregarTextura("assets/sprites/minerio_magnetita.png");
    _sprites.cobre     = carregarTextura("assets/sprites/minerio_cobre.png");
    _sprites.ouro      = carregarTextura("assets/sprites/minerio_ouro.png");
    _sprites.muro      = carregarTextura("assets/sprites/muro.png");
    _sprites.overlay   = carregarTextura("assets/sprites/overlay.png");

    for (int j = 0; j < 2; ++j)
        for (int f = 0; f < 4; ++f)
            for (int fr = 0; fr < 2; ++fr) {
                std::string path = "assets/sprites/robo_" + std::to_string(j + 1)
                                 + "_" + FACING_NOMES[f]
                                 + "_" + std::to_string(fr + 1) + ".png";
                _sprites.robo[j][f][fr] = carregarTextura(path);
            }
}

void AssetsHandler::carregarIcones() {
    _sprites.icone_magnetita = carregarTextura("assets/sprites/icone_magnetita.png");
    _sprites.icone_cobre     = carregarTextura("assets/sprites/icone_cobre.png");
    _sprites.icone_ouro      = carregarTextura("assets/sprites/icone_ouro.png");
    _sprites.icone_pedra     = carregarTextura("assets/sprites/icone_pedra.png");
}
