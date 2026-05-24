#ifndef MINECIN_CORE_JOGO_H
#define MINECIN_CORE_JOGO_H

#include "core/Tela.h"
#include "core/GerenciadorAssets.h"
#include "enums/ModoJogo.h"
#include <memory>

class IRenderer;
class IProvedorInput;

class Jogo {
    IRenderer&            _renderer;
    IProvedorInput&       _input;
    GerenciadorAssets     _assets;
    std::unique_ptr<Tela> _telaAtual;
    bool                  _terminou = false;
public:
    Jogo(IRenderer& renderer, IProvedorInput& input);
    void inicializar(ModoJogo modo);
    void processar(float dt);
    bool terminou() const { return _terminou; }
    void imprimirResumo() const;
};

#endif // MINECIN_CORE_JOGO_H
