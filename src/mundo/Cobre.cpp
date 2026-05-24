#include "mundo/Cobre.h"
#include "entidades/Personagem.h"

Cobre::Cobre(Rect b, TextureHandle tex) : Pedra(b, 1, tex) {}

void Cobre::quebrar(Personagem& p) {
    p.inventario.cobre += 1;
    _morto = true;
}
