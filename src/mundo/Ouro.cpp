#include "mundo/Ouro.h"
#include "entidades/Personagem.h"
#include <spdlog/spdlog.h>

Ouro::Ouro(Rect b, TextureHandle tex) : Pedra(b, 1, tex) {}

void Ouro::quebrar(Personagem& p) {
    spdlog::debug("Ouro::quebrar dur={} morto={}", _durabilidade, _durabilidade <= 0);
    p.inventario.ouro += 1;
    _morto = true;
}
