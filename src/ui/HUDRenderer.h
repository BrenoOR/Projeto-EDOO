#ifndef MINECIN_UI_RENDERIZADORHUD_H
#define MINECIN_UI_RENDERIZADORHUD_H

#include "ui/Icone.h"
#include "ui/HUDData.h"
#include "renderer/IRenderer.h"
#include <memory>

class AssetsHandler;

class RenderizadorHUD {
    std::unique_ptr<IconeMagnetita> _iMag;
    std::unique_ptr<IconeCobre>     _iCob;
    std::unique_ptr<IconeOuro>      _iOur;
    std::unique_ptr<IconePedra>     _iPed;

    static constexpr int   HUD_Y    = 640;
    static constexpr int   HUD_H    = 40;
    static constexpr float ICO_TAM  = 20.0f;

    void desenharSlot(IRenderer& r, float x, float y,
                      const Icone& ico, int valor, Color cor) const;
    void desenharNumero(IRenderer& r, int valor,
                        float x, float y, Color cor) const;
    void desenharDigito(IRenderer& r, int d,
                        float x, float y, Color cor) const;
    void desenharTimer(IRenderer& r, const HUDData& d) const;

public:
    void carregar(AssetsHandler& assets);
    void mostrar(IRenderer& r, const HUDData& dados) const;
};

#endif // MINECIN_UI_RENDERIZADORHUD_H
