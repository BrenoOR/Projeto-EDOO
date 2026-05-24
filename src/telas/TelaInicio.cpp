#include "core/IInputProvider.h"
#include "telas/TelaInicio.h"
#include "telas/TelaJogo.h"
#include "renderer/FonteBitmap.h"

TelaInicio::TelaInicio(AssetsHandler& assets, ModoJogo modo, bool simulacao)
    : _assets(assets), _modo(modo), _simulacao(simulacao) {}

std::unique_ptr<Tela> TelaInicio::atualizar(float dt, const IInputProvider& input) {
    if (input.wasPressed(Tecla::T) || input.isHeld(Tecla::T))
        return std::make_unique<TelaJogo>(_assets, ModoJogo::Tempo, _simulacao);
    if (input.wasPressed(Tecla::B) || input.isHeld(Tecla::B))
        return std::make_unique<TelaJogo>(_assets, ModoJogo::Blocos, _simulacao);

    _espera += dt;
    if (_espera >= TIMEOUT && _simulacao)
        return std::make_unique<TelaJogo>(_assets, _modo, _simulacao);

    return nullptr;
}

void TelaInicio::mostrar(IRenderer& r) const {
    r.drawRect({0, 0, 680, 680}, {10, 10, 20});

    const std::string titulo = "MINECIN";
    float tx = (680.0f - larguraTexto(titulo, 4.0f)) / 2.0f;
    desenharTexto(r, titulo, tx, 180, 4.0f, {255, 200, 50});

    // opcao T
    r.drawRect({160, 310, 160, 70}, {30, 60, 120});
    r.drawRect({160, 310, 160, 2},  {100, 160, 220});
    r.drawRect({160, 378, 160, 2},  {100, 160, 220});
    r.drawRect({160, 310, 2, 70},   {100, 160, 220});
    r.drawRect({318, 310, 2, 70},   {100, 160, 220});
    desenharTexto(r, "[T]",   178, 326, 3.0f, {150, 200, 255});
    desenharTexto(r, "TEMPO", 173, 352, 2.0f, {150, 200, 255});

    // opcao B
    r.drawRect({360, 310, 160, 70}, {120, 40, 30});
    r.drawRect({360, 310, 160, 2},  {220, 100, 80});
    r.drawRect({360, 378, 160, 2},  {220, 100, 80});
    r.drawRect({360, 310, 2, 70},   {220, 100, 80});
    r.drawRect({518, 310, 2, 70},   {220, 100, 80});
    desenharTexto(r, "[B]",    378, 326, 3.0f, {255, 150, 120});
    desenharTexto(r, "BLOCOS", 370, 352, 2.0f, {255, 150, 120});

    const std::string inst = "ESCOLHA O MODO DE JOGO";
    float ix = (680.0f - larguraTexto(inst, 2.0f)) / 2.0f;
    desenharTexto(r, inst, ix, 430, 2.0f, {120, 120, 140});
}
