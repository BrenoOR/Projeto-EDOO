#include "ui/HUDRenderer.h"
#include "core/AssetsHandler.h"

// ── Font bitmap 3×5 para dígitos 0–9 ─────────────────────────────
// Cada dígito: array de 5 linhas, cada linha = 3 bits (MSB=esquerda)
static const uint8_t DIGITOS[10][5] = {
    {0b111, 0b101, 0b101, 0b101, 0b111}, // 0
    {0b010, 0b110, 0b010, 0b010, 0b111}, // 1
    {0b111, 0b001, 0b111, 0b100, 0b111}, // 2
    {0b111, 0b001, 0b111, 0b001, 0b111}, // 3
    {0b101, 0b101, 0b111, 0b001, 0b001}, // 4
    {0b111, 0b100, 0b111, 0b001, 0b111}, // 5
    {0b111, 0b100, 0b111, 0b101, 0b111}, // 6
    {0b111, 0b001, 0b001, 0b001, 0b001}, // 7
    {0b111, 0b101, 0b111, 0b101, 0b111}, // 8
    {0b111, 0b101, 0b111, 0b001, 0b111}, // 9
};

void RenderizadorHUD::carregar(AssetsHandler& assets) {
    _iMag = std::make_unique<IconeMagnetita>(); _iMag->carregar(assets);
    _iCob = std::make_unique<IconeCobre>();     _iCob->carregar(assets);
    _iOur = std::make_unique<IconeOuro>();      _iOur->carregar(assets);
    _iPed = std::make_unique<IconePedra>();     _iPed->carregar(assets);
}

void RenderizadorHUD::mostrar(IRenderer& r, const HUDData& d) const {
    // fundo do HUD
    r.drawRect({0, float(HUD_Y), 680, float(HUD_H)}, {30, 30, 30});
    // linha separadora
    r.drawRect({0, float(HUD_Y), 680, 1}, {60, 60, 60});

    const float Y = HUD_Y + 10.0f;

    // ── Jogador 1 (esquerda) ─────────────────────────────────────────────
    Color AZUL = {100, 160, 220};
    desenharSlot(r,  4, Y, *_iMag, d.p1.magnetita, AZUL);
    desenharSlot(r, 74, Y, *_iCob, d.p1.cobre,     AZUL);
    desenharSlot(r,144, Y, *_iOur, d.p1.ouro,      AZUL);
    desenharSlot(r,214, Y, *_iPed, d.p1.pedra,     AZUL);

    // ── Timer / contador central ───────────────────────────────────
    desenharTimer(r, d);

    // ── Jogador 2 (direita) ──────────────────────────────────────────────
    Color VERM = {220, 100,  80};
    desenharSlot(r,356, Y, *_iPed, d.p2.pedra,     VERM);
    desenharSlot(r,426, Y, *_iOur, d.p2.ouro,      VERM);
    desenharSlot(r,496, Y, *_iCob, d.p2.cobre,     VERM);
    desenharSlot(r,566, Y, *_iMag, d.p2.magnetita, VERM);
}

void RenderizadorHUD::desenharSlot(IRenderer& r, float x, float y,
                                   const Icone& ico, int valor, Color cor) const {
    ico.mostrar(r, {x, y, ICO_TAM, ICO_TAM});
    desenharNumero(r, valor, x + ICO_TAM + 3, y + 6, cor);
}

void RenderizadorHUD::desenharNumero(IRenderer& r, int valor,
                                     float x, float y, Color cor) const {
    // máximo 2 dígitos visíveis
    int v = (valor > 99) ? 99 : (valor < 0 ? 0 : valor);
    if (v >= 10)
        desenharDigito(r, v / 10, x,     y, cor);
    desenharDigito(r, v % 10, x + (v >= 10 ? 9 : 0), y, cor);
}

void RenderizadorHUD::desenharDigito(IRenderer& r, int d,
                                     float x, float y, Color cor) const {
    constexpr float PIXEL = 2.0f; // cada "pixel" do bitmap = 2×2 px reais
    const auto& padrão = DIGITOS[d];
    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (padrão[row] & (0b100 >> col)) {
                r.drawRect({x + col * PIXEL, y + row * PIXEL, PIXEL, PIXEL}, cor);
            }
        }
    }
}

void RenderizadorHUD::desenharTimer(IRenderer& r, const HUDData& d) const {
    const float CX = 340.0f, Y = HUD_Y + 10.0f;

    if (d.modoTempo) {
        // segundos restantes
        int segs = d.ticksRestantes / 30;

        // cor por faixa: verde > 20s, amarelo > 10s, vermelho ≤ 10s
        Color cor;
        if (segs > 20)      cor = {80, 200, 80};
        else if (segs > 10) cor = {220, 200, 50};
        else                cor = {220, 60, 60};

        // barra de progresso
        float ratio   = float(d.ticksRestantes) / 1500.0f;
        float bar_w   = 60.0f * ratio;
        r.drawRect({CX - 30, Y + 15, 60,   4}, {60, 60, 60});
        r.drawRect({CX - 30, Y + 15, bar_w, 4}, cor);

        // dígitos MM:SS
        int mins = segs / 60;
        int ss   = segs % 60;
        float dx = CX - 19;
        desenharDigito(r, mins % 10, dx,      Y, cor);
        // dois pontos
        r.drawRect({dx + 8,  Y + 1, 2, 2}, cor);
        r.drawRect({dx + 8,  Y + 5, 2, 2}, cor);
        desenharDigito(r, ss / 10,   dx + 12, Y, cor);
        desenharDigito(r, ss % 10,   dx + 21, Y, cor);

    } else {
        // modo Blocos: mostra mineráveis restantes
        Color cor = {180, 180, 180};
        desenharNumero(r, d.mineraveisRestantes, CX - 12, Y, cor);
        // ícone de pedra no centro
        if (_iPed->tex())
            r.drawTexture(_iPed->tex(), {CX - 30, Y, 16, 16});
    }
}
