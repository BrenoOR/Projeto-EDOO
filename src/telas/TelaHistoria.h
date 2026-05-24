#ifndef MINECIN_TELAS_TELAHISTORIA_H
#define MINECIN_TELAS_TELAHISTORIA_H

#include "core/Tela.h"
#include "enums/ModoJogo.h"

class AssetsHandler;

class TelaHistoria : public Tela {
    AssetsHandler& _assets;
    ModoJogo         _modo;
public:
    TelaHistoria(AssetsHandler& assets, ModoJogo modo);
    std::unique_ptr<Tela> atualizar(float dt, const IInputProvider& input) override;
};

#endif // MINECIN_TELAS_TELAHISTORIA_H
