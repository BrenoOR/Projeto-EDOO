#ifndef MINECIN_UI_HUDDATA_H
#define MINECIN_UI_HUDDATA_H

#include "entidades/Personagem.h"

struct HUDData {
    Inventario p1;
    Inventario p2;
    int  ticksRestantes      = 0;
    bool modoTempo           = true;
    int  mineraveisRestantes = 0;
};

#endif // MINECIN_UI_HUDDATA_H
