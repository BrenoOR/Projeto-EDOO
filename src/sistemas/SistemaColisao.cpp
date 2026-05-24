#include "sistemas/SistemaColisao.h"
#include "entidades/Personagem.h"
#include "mundo/Pedra.h"
#include "mundo/Mapa.h"
#include <algorithm>

void SistemaColisao::resolverMovimento(Personagem& p, const Mapa& mapa) {
    Rect r = p.getLimites();

    int colMin = std::max(0, static_cast<int>(r.x / Mapa::TAM_BLOCO));
    int colMax = std::min(Mapa::COLS - 1, static_cast<int>((r.right()  - 1.0f) / Mapa::TAM_BLOCO));
    int rowMin = std::max(0, static_cast<int>(r.y / Mapa::TAM_BLOCO));
    int rowMax = std::min(Mapa::ROWS - 1, static_cast<int>((r.bottom() - 1.0f) / Mapa::TAM_BLOCO));

    for (int row = rowMin; row <= rowMax; ++row) {
        for (int col = colMin; col <= colMax; ++col) {
            auto opt = mapa.blocoEm(col, row);
            if (!opt) continue;

            r = p.getLimites();
            const Rect& b = (*opt)->bounds;
            if (!r.intersects(b)) continue;

            float ox = std::min(r.right() - b.x, b.right() - r.x);
            float oy = std::min(r.bottom() - b.y, b.bottom() - r.y);

            if (ox <= oy) {
                float push = (r.center().x < b.center().x) ? -ox : ox;
                p.aplicarMovimento({push, 0.0f});
            } else {
                float push = (r.center().y < b.center().y) ? -oy : oy;
                p.aplicarMovimento({0.0f, push});
            }
        }
    }
}

void SistemaColisao::resolverAcao(Personagem& atacante, Personagem& alvo,
                                   const std::vector<Pedra*>& pedras) {
    if (!atacante.isPicaretaAtiva() && !atacante.isRestaurarAtiva()) return;

    Rect picareta = atacante.getRectPicareta();

    if (atacante.isPicaretaAtiva()) {
        if (picareta.intersects(alvo.getLimites()))
            alvo.voltarParaSpawn();

        for (Pedra* p : pedras)
            if (p && !p->estaMorto() && picareta.intersects(p->bounds))
                p->quebrar(atacante);
    }

    if (atacante.isRestaurarAtiva()) {
        for (Pedra* p : pedras)
            if (p && !p->estaMorto() && picareta.intersects(p->bounds))
                p->restaurar(atacante);
    }
}
