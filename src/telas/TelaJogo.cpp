#include "telas/TelaJogo.h"
#include "telas/TelaFinal.h"
#include "core/GerenciadorAssets.h"

TelaJogo::TelaJogo(GerenciadorAssets& assets, ModoJogo modo)
    : _assets(assets)
    , _modo(modo)
    , _p1({0.0f, 610.0f})
    , _p2({650.0f, 610.0f})
{
    _mapa.construir(_assets);
}

std::unique_ptr<Tela> TelaJogo::atualizar(float, const IProvedorInput& input) {
    _p1.processarInput(input, 0);
    _p2.processarInput(input, 1);

    _colisao.resolverMovimento(_p1, _mapa);
    _colisao.resolverMovimento(_p2, _mapa);

    _colisao.resolverAcao(_p1, _p2, _mapa.blocos());
    _colisao.resolverAcao(_p2, _p1, _mapa.blocos());

    _mapa.removerMortos();

    _p1.limitarPosicao({0.0f, 0.0f, LARGURA_MUNDO, ALTURA_MUNDO});
    _p2.limitarPosicao({0.0f, 0.0f, LARGURA_MUNDO, ALTURA_MUNDO});

    ++_ticks;

    if (jogoAcabou())
        return std::make_unique<TelaFinal>(
            _p1.calcularPontuacao(),
            _p2.calcularPontuacao());

    return nullptr;
}

bool TelaJogo::jogoAcabou() const {
    if (_modo == ModoJogo::Tempo)  return _ticks >= TICKS_TEMPO;
    if (_modo == ModoJogo::Blocos) return _mapa.contarMineraveis() == 0;
    return false;
}

void TelaJogo::mostrar(IRenderer& r) const {
    _mapa.mostrar(r);
    _p1.mostrar(r);
    _p2.mostrar(r);
}
