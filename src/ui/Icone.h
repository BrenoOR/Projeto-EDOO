#ifndef MINECIN_UI_ICONE_H
#define MINECIN_UI_ICONE_H

#include "renderer/IRenderer.h"
#include "tipos/Rect.h"

class AssetsHandler;

class Icone {
protected:
    TextureHandle _tex = 0;
public:
    virtual ~Icone() = default;
    virtual void carregar(AssetsHandler& assets) = 0;
    void mostrar(IRenderer& r, Rect dst) const;
    TextureHandle tex() const { return _tex; }
};

class IconeMagnetita : public Icone {
public:
    void carregar(AssetsHandler& assets) override;
};

class IconeCobre : public Icone {
public:
    void carregar(AssetsHandler& assets) override;
};

class IconeOuro : public Icone {
public:
    void carregar(AssetsHandler& assets) override;
};

class IconePedra : public Icone {
public:
    void carregar(AssetsHandler& assets) override;
};

#endif // MINECIN_UI_ICONE_H
