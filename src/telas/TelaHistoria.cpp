#include "telas/TelaHistoria.h"
#include "telas/TelaInicio.h"

TelaHistoria::TelaHistoria(GerenciadorAssets& assets, ModoJogo modo)
    : _assets(assets), _modo(modo) {}

std::unique_ptr<Tela> TelaHistoria::atualizar(float, const IProvedorInput&) {
    // Animacao de digitação letra a letra
    return std::make_unique<TelaInicio>(_assets, _modo);
}
