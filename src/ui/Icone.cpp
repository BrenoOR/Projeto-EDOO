#include "ui/Icone.h"
#include "core/AssetsHandler.h"

void Icone::mostrar(IRenderer& r, Rect dst) const {
    if (_tex)
        r.drawTexture(_tex, dst);
    else
        r.drawRect(dst, {80, 80, 80});
}

void IconeMagnetita::carregar(AssetsHandler& assets) {
    _tex = assets.sprites().icone_magnetita;
}
void IconeCobre::carregar(AssetsHandler& assets) {
    _tex = assets.sprites().icone_cobre;
}
void IconeOuro::carregar(AssetsHandler& assets) {
    _tex = assets.sprites().icone_ouro;
}
void IconePedra::carregar(AssetsHandler& assets) {
    _tex = assets.sprites().icone_pedra;
}
