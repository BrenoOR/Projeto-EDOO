#include "telas/TelaFinal.h"
#include "core/IInputProvider.h"
#include "renderer/FonteBitmap.h"

TelaFinal::TelaFinal(int p1, int p2)
    : _pontuacao1(p1), _pontuacao2(p2) {}

std::unique_ptr<Tela> TelaFinal::atualizar(float dt, const IInputProvider& input) {
    _tempo += dt;

    if (!_saindo && _tempo >= FADE_IN && (input.wasPressed(Tecla::Enter) || input.isHeld(Tecla::Enter)))
        _saindo = true;

    if (_saindo) {
        _tempoSaida += dt;
        if (_tempoSaida >= FADE_OUT)
            _encerrado = true;
    }

    return nullptr;
}

void TelaFinal::mostrar(IRenderer& r) const {
    float alpha = 1.0f;
    if (_tempo < FADE_IN)
        alpha = _tempo / FADE_IN;
    else if (_saindo)
        alpha = 1.0f - (_tempoSaida / FADE_OUT);
    alpha = std::max(0.0f, std::min(1.0f, alpha));

    r.setGlobalAlpha(alpha);
    r.drawRect({0, 0, 680, 680}, {10, 10, 20});

    // título
    const std::string titulo = "FIM DE JOGO";
    desenharTexto(r, titulo,
                  (680.0f - larguraTexto(titulo, 3.0f)) / 2.0f,
                  120, 3.0f, {255, 200, 50});

    // painel P1
    bool p1vence = _pontuacao1 > _pontuacao2;
    bool empate  = _pontuacao1 == _pontuacao2;
    Color corP1  = p1vence  ? Color{80, 200, 80} : Color{100, 160, 220};
    Color corP2  = (!p1vence && !empate) ? Color{80, 200, 80} : Color{220, 100, 80};

    r.drawRect({60, 220, 240, 200}, {20, 20, 40});
    desenharTexto(r, "JOGADOR 1", 80, 240, 2.0f, corP1);
    desenharTexto(r, "PONTOS",    80, 280, 2.0f, {140, 140, 160});

    std::string s1 = std::to_string(_pontuacao1);
    desenharTexto(r, s1,
                  (180.0f - larguraTexto(s1, 4.0f)) / 2.0f + 60,
                  310, 4.0f, corP1);

    if (p1vence)
        desenharTexto(r, "VENCEDOR!", 75, 380, 2.0f, {255, 220, 50});

    // painel P2
    r.drawRect({380, 220, 240, 200}, {20, 20, 40});
    desenharTexto(r, "JOGADOR 2", 400, 240, 2.0f, corP2);
    desenharTexto(r, "PONTOS",    400, 280, 2.0f, {140, 140, 160});

    std::string s2 = std::to_string(_pontuacao2);
    desenharTexto(r, s2,
                  (180.0f - larguraTexto(s2, 4.0f)) / 2.0f + 380,
                  310, 4.0f, corP2);

    if (!p1vence && !empate)
        desenharTexto(r, "VENCEDOR!", 395, 380, 2.0f, {255, 220, 50});

    if (empate) {
        const std::string emp = "EMPATE!";
        desenharTexto(r, emp,
                      (680.0f - larguraTexto(emp, 3.0f)) / 2.0f,
                      440, 3.0f, {220, 220, 80});
    }

    if (_tempo >= FADE_IN) {
        const std::string hint = "PRESSIONE ENTER PARA SAIR";
        desenharTexto(r, hint,
                      (680.0f - larguraTexto(hint, 1.5f)) / 2.0f,
                      620, 1.5f, {120, 120, 140});
    }

    r.setGlobalAlpha(1.0f);
}
