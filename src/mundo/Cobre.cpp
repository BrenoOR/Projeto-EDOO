#include "mundo/Cobre.h"
#include "entidades/Personagem.h"
#include <spdlog/spdlog.h>

Cobre::Cobre(Rect b, TextureHandle tex) : Pedra(b, 1, tex) {}

void Cobre::quebrar(Personagem& p) {
    spdlog::debug("Cobre::quebrar dur={} morto={}", _durabilidade, _durabilidade <= 0);
    p.inventario.cobre += 1;
    _morto = true;
}
