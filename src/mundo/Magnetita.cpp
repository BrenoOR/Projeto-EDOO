#include "mundo/Magnetita.h"
#include "entidades/Personagem.h"

Magnetita::Magnetita(Rect b, TextureHandle tex) : Pedra(b, 1, tex) {}

void Magnetita::quebrar(Personagem& p) {
    p.inventario.magnetita += 1;
    p.danoPicareta = 1 + p.inventario.magnetita / 2;
    _morto = true;
}
