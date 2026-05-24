#include "core/Jogo.h"
#include "telas/TelaHistoria.h"
#include "telas/TelaFinal.h"
#include <iostream>

Jogo::Jogo(IRenderer& renderer, IProvedorInput& input)
    : _renderer(renderer), _input(input), _assets(renderer) {}

void Jogo::inicializar(ModoJogo modo) {
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
