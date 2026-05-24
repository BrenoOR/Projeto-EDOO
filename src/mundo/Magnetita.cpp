#include "mundo/Magnetita.h"
#include "entidades/Personagem.h"
#include <spdlog/spdlog.h>

Magnetita::Magnetita(Rect b, TextureHandle tex) : Pedra(b, 1, tex) {}

void Magnetita::quebrar(Personagem& p) {
    spdlog::debug("Magnetita::quebrar dur={} morto={}", _durabilidade, _durabilidade <= 0);
    p.inventario.magnetita += 1;
    p.danoPicareta = 1 + p.inventario.magnetita / 2;
    _morto = true;
}
