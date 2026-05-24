#ifndef MINECIN_TELAS_TELAINICIO_H
#define MINECIN_TELAS_TELAINICIO_H

#include "core/Tela.h"
#include "enums/ModoJogo.h"

class AssetsHandler;

class TelaInicio : public Tela {
    AssetsHandler& _assets;
    ModoJogo       _modo;
    float          _espera = 0.0f;
    bool          _simulacao;

    // Constante de espera na tela de inicio
    static constexpr float TIMEOUT = 2.0f;

public:
    TelaInicio(AssetsHandler& assets, ModoJogo modo, bool simulacao);
    std::unique_ptr<Tela> atualizar(float dt, const IInputProvider& input) override;
    void mostrar(IRenderer& r) const override;
};

#endif // MINECIN_TELAS_TELAINICIO_H
