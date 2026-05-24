#include "mundo/Ouro.h"
#include "entidades/Personagem.h"

Ouro::Ouro(Rect b, TextureHandle tex) : Pedra(b, 1, tex) {}

void Ouro::quebrar(Personagem& p) {
    p.inventario.ouro += 1;
    _morto = true;
}
