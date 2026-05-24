#ifndef MINECIN_TELAS_TELAHISTORIA_H
#define MINECIN_TELAS_TELAHISTORIA_H

#include "core/Tela.h"
#include "enums/ModoJogo.h"

class GerenciadorAssets;

class TelaHistoria : public Tela {
    GerenciadorAssets& _assets;
    ModoJogo           _modo;
public:
    TelaHistoria(GerenciadorAssets& assets, ModoJogo modo);
    std::unique_ptr<Tela> atualizar(float dt, const IProvedorInput& input) override;
};

#endif // MINECIN_TELAS_TELAHISTORIA_H
