#include "telas/TelaFinal.h"

TelaFinal::TelaFinal(int p1, int p2)
    : _pontuacao1(p1), _pontuacao2(p2) {}

std::unique_ptr<Tela> TelaFinal::atualizar(float, const IProvedorInput&) {
    _encerrado = true;
    return nullptr;
}
