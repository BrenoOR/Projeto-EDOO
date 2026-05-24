#include "telas/TelaInicio.h"
#include "telas/TelaJogo.h"

TelaInicio::TelaInicio(AssetsHandler& assets, ModoJogo modo)
    : _assets(assets), _modo(modo) {}

std::unique_ptr<Tela> TelaInicio::atualizar(float, const IInputProvider& input) {
    // Aguarda Tecla::T (Tempo) ou Tecla::B (Blocos)
    return std::make_unique<TelaJogo>(_assets, _modo);
}
