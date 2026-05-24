#ifndef MINECIN_MUNDO_COBRE_H
#define MINECIN_MUNDO_COBRE_H

#include "mundo/Pedra.h"

class Cobre : public Pedra {
public:
    Cobre(Rect bounds, TextureHandle tex = 0);
    void quebrar(Personagem& p) override;
    void restaurar(Personagem&) override {}
};

#endif // MINECIN_MUNDO_COBRE_H
