#ifndef MINECIN_TELAS_TELAHISTORIA_H
#define MINECIN_TELAS_TELAHISTORIA_H

#include "core/Tela.h"
#include "enums/ModoJogo.h"
#include <string>

class AssetsHandler;

class TelaHistoria : public Tela {
    AssetsHandler& _assets;
    ModoJogo       _modo;
    bool           _simulacao;

    static const std::string TEXTO;
    int   _charAtual = 0;
    float _acumulado = 0.0f;
    float _espera    = 0.0f;

    static constexpr float CHARS_POR_SEG = 20.0f;
    static constexpr float ESPERA_FINAL  = 1.7f;

public:
    TelaHistoria(AssetsHandler& assets, ModoJogo modo, bool simulacao);
    std::unique_ptr<Tela> atualizar(float dt, const IInputProvider& input) override;
    void mostrar(IRenderer& r) const override;
};

#endif // MINECIN_TELAS_TELAHISTORIA_H
