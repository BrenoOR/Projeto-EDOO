#ifndef MINECIN_MUNDO_OURO_H
#define MINECIN_MUNDO_OURO_H

#include "mundo/Pedra.h"

class Ouro : public Pedra {
public:
    Ouro(Rect bounds, TextureHandle tex = 0);
    void quebrar(Personagem& p) override;
    void restaurar(Personagem&) override {}
};

#endif // MINECIN_MUNDO_OURO_H
