#ifndef MINECIN_TELAS_TELAINICIO_H
#define MINECIN_TELAS_TELAINICIO_H

#include "core/Tela.h"
#include "enums/ModoJogo.h"

class AssetsHandler;

class TelaInicio : public Tela {
    AssetsHandler& _assets;
    ModoJogo         _modo;
public:
    TelaInicio(AssetsHandler& assets, ModoJogo modo);
    std::unique_ptr<Tela> atualizar(float dt, const IInputProvider& input) override;
};

#endif // MINECIN_TELAS_TELAINICIO_H
