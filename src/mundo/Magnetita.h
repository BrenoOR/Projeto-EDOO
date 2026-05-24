#ifndef MINECIN_MUNDO_MAGNETITA_H
#define MINECIN_MUNDO_MAGNETITA_H

#include "mundo/Pedra.h"

class Magnetita : public Pedra {
public:
    Magnetita(Rect bounds, TextureHandle tex = 0);
    void quebrar(Personagem& p) override;
    void restaurar(Personagem&) override {}
};

#endif // MINECIN_MUNDO_MAGNETITA_H
