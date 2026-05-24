#ifndef MINECIN_CORE_JOGO_H
#define MINECIN_CORE_JOGO_H

#include "core/Tela.h"
#include "core/AssetsHandler.h"
#include "enums/ModoJogo.h"
#include <functional>
#include <memory>

class IRenderer;
class IInputProvider;

class Jogo {
    IRenderer&            _renderer;
    IInputProvider&       _input;
    AssetsHandler         _assets;
    std::unique_ptr<Tela> _telaAtual;
    bool                  _terminou = false;
public:
    Jogo(IRenderer& renderer, IInputProvider& input);
    void inicializar(ModoJogo modo);
    void processar(float dt);
    void mostrar() const;
    bool terminou() const { return _terminou; }
    void imprimirResumo() const;

    void executar(ModoJogo modo,
                  const std::function<bool()>&  shouldQuit,
                  const std::function<void()>&  pollEvents,
                  const std::function<void()>&  swapBuffers);
};

#endif // MINECIN_CORE_JOGO_H
