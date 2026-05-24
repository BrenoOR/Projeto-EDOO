#ifndef MINECIN_MUNDO_MURO_H
#define MINECIN_MUNDO_MURO_H

#include "mundo/Pedra.h"

class Muro : public Pedra {
public:
    Muro(Rect bounds, TextureHandle tex = 0);
    void quebrar(Personagem&) override {}
    void restaurar(Personagem&) override {}
    bool eDestruivel() const override { return false; }
};

#endif // MINECIN_MUNDO_MURO_H
