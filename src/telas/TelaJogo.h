#ifndef MINECIN_TELAS_TELAJOGO_H
#define MINECIN_TELAS_TELAJOGO_H

#include "core/Tela.h"
#include "enums/ModoJogo.h"
#include "mundo/Mapa.h"
#include "entidades/Personagem.h"
#include "sistemas/SistemaColisao.h"
#include "ui/HUDRenderer.h"

class AssetsHandler;

class TelaJogo : public Tela {
public:
    // Contador do modo Tempo: 30 FPS x 50 s
    static constexpr int   TICKS_TEMPO   = 1500;
    static constexpr float LARGURA_MUNDO = 680.0f;
    static constexpr float ALTURA_MUNDO  = 640.0f;

    TelaJogo(AssetsHandler& assets, ModoJogo modo, bool simulacao);
    std::unique_ptr<Tela> atualizar(float dt, const IInputProvider& input) override;
    void mostrar(IRenderer& r) const override;

private:
    AssetsHandler& _assets;
    ModoJogo           _modo;
    bool               _simulacao;
    Mapa               _mapa;
    Personagem         _p1;
    Personagem         _p2;
    SistemaColisao     _colisao;
    RenderizadorHUD    _hud;
    int                _ticks = 0;

    bool jogoAcabou() const;
};

#endif // MINECIN_TELAS_TELAJOGO_H
