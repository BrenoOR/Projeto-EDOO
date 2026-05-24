#ifndef MINECIN_TELAS_TELAINICIO_H
#define MINECIN_TELAS_TELAINICIO_H

#include "core/Tela.h"
#include "enums/ModoJogo.h"

class GerenciadorAssets;

class TelaInicio : public Tela {
    GerenciadorAssets& _assets;
    ModoJogo           _modo;
public:
    TelaInicio(GerenciadorAssets& assets, ModoJogo modo);
    std::unique_ptr<Tela> atualizar(float dt, const IProvedorInput& input) override;
};

#endif // MINECIN_TELAS_TELAINICIO_H
