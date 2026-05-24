#include "mundo/Pedra.h"
#include "entidades/Personagem.h"
#include <spdlog/spdlog.h>

Pedra::Pedra(Rect b, int dur, TextureHandle tex)
    : bounds(b), texture(tex), _durabilidade(dur), _durabilidadeMax(dur) {}

void Pedra::mostrar(IRenderer& r) const {
    if (texture)
        r.drawTexture(texture, bounds);
    else
        r.drawRect(bounds, {120, 120, 120});

    // overlay de dano
    if (_durabilidadeMax > 1) {
        float ratio = float(_durabilidade) / float(_durabilidadeMax);
        if (ratio < 1.0f) {
            uint8_t alpha = uint8_t((1.0f - ratio) * 180.0f);
            r.drawRect(bounds, {200, 50, 50, alpha});
        }
    }
}

void Pedra::quebrar(Personagem& p) {
    _durabilidade -= p.danoPicareta;
    spdlog::debug("Pedra::quebrar dur={} morto={}", _durabilidade, _durabilidade <= 0);
    if (_durabilidade <= 0) {
        p.inventario.pedra += 2;
        _morto = true;
    }
}

void Pedra::restaurar(Personagem& p) {
    while (_durabilidade <= 31 && p.inventario.pedra > 0) {
        _durabilidade += 1;
        p.inventario.pedra -= 1;
    }
}
