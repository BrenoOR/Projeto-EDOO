#include "core/Jogo.h"
#include "telas/TelaHistoria.h"
#include "telas/TelaFinal.h"
#include "renderer/IRenderer.h"
#include "tipos/Color.h"
#include <spdlog/spdlog.h>
#include <chrono>
#include <iostream>

Jogo::Jogo(IRenderer& renderer, IInputProvider& input)
    : _renderer(renderer), _input(input), _assets(renderer) {}

void Jogo::inicializar(ModoJogo modo) {
    _assets.carregarTodos();
    _assets.carregarIcones();
    _telaAtual = std::make_unique<TelaHistoria>(_assets, modo);
}

void Jogo::processar(float dt) {
    if (!_telaAtual || _terminou)
        return;

    auto proxima = _telaAtual->atualizar(dt, _input);
    if (proxima)
        _telaAtual = std::move(proxima);

    auto* final = dynamic_cast<TelaFinal*>(_telaAtual.get());
    if (final && final->encerrou())
        _terminou = true;
}

void Jogo::mostrar() const {
    if (_telaAtual)
        _telaAtual->mostrar(_renderer);
}

void Jogo::executar(ModoJogo modo,
                    const std::function<bool()>&  shouldQuit,
                    const std::function<void()>&  pollEvents,
                    const std::function<void()>&  swapBuffers)
{
    using Clock = std::chrono::steady_clock;
    using Dur   = std::chrono::duration<double>;

    inicializar(modo);

    constexpr double PASSO    = 1.0 / 30.0;
    constexpr int    MAX_ITER = 5;
    double           lag      = 0.0;
    auto             anterior = Clock::now();

    spdlog::info("Jogo::executar iniciado");

    while (!terminou() && !shouldQuit()) {
        pollEvents();

        auto   agora = Clock::now();
        double delta = Dur(agora - anterior).count();
        anterior     = agora;
        if (delta > 0.25) delta = 0.25; // evita lag

        lag += delta;
        int iter = 0;
        while (lag >= PASSO && iter < MAX_ITER) {
            processar((float)PASSO);
            lag  -= PASSO;
            ++iter;
        }

        _renderer.beginFrame(Color::black());
        mostrar();
        _renderer.endFrame();
        swapBuffers();
    }

    spdlog::info("Jogo::executar finalizado");
}

void Jogo::imprimirResumo() const {
    auto* final = dynamic_cast<const TelaFinal*>(_telaAtual.get());
    if (!final) return;
    std::cout << "=== Fim de Jogo ===\n";
    std::cout << "P1  pts=" << final->getPontuacao1() << "\n";
    std::cout << "P2  pts=" << final->getPontuacao2() << "\n";
    if (final->getPontuacao1() > final->getPontuacao2())
        std::cout << "Vencedor: P1\n";
    else if (final->getPontuacao2() > final->getPontuacao1())
        std::cout << "Vencedor: P2\n";
    else
        std::cout << "Empate!\n";
}
