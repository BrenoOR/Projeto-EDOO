#ifndef MINECIN_TELAS_TELAFINAL_H
#define MINECIN_TELAS_TELAFINAL_H

#include "core/Tela.h"

class TelaFinal : public Tela {
    int   _pontuacao1;
    int   _pontuacao2;
    bool  _encerrado  = false;
    bool  _saindo     = false;
    float _tempo      = 0.0f;
    float _tempoSaida = 0.0f;

    static constexpr float FADE_IN  = 0.5f;
    static constexpr float FADE_OUT = 0.5f;

public:
    TelaFinal(int p1, int p2);
    std::unique_ptr<Tela> atualizar(float dt, const IInputProvider& input) override;
    void mostrar(IRenderer& r) const override;

    bool encerrou()     const { return _encerrado;  }
    int getPontuacao1() const { return _pontuacao1; }
    int getPontuacao2() const { return _pontuacao2; }
};

#endif // MINECIN_TELAS_TELAFINAL_H
