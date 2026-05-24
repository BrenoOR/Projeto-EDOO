#include "mundo/Pedra.h"
#include "entidades/Personagem.h"

Pedra::Pedra(Rect b, int dur, TextureHandle tex)
    : bounds(b), texture(tex), _durabilidade(dur) {}

void Pedra::mostrar(IRenderer& r) const {
    r.drawRect(bounds, Color::white());
}

void Pedra::quebrar(Personagem& p) {
    _durabilidade -= p.danoPicareta;
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
