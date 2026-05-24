#ifndef MINECIN_MUNDO_PEDRA_H
#define MINECIN_MUNDO_PEDRA_H

#include "tipos/Rect.h"
#include "renderer/IRenderer.h"

class Personagem;

class Pedra {
public:
    Rect bounds;
    TextureHandle texture = 0;

    Pedra() = default;
    Pedra(Rect bounds, int durabilidade, TextureHandle tex = 0);
    virtual ~Pedra() = default;

    virtual void mostrar(IRenderer& r) const;
    virtual void quebrar(Personagem& p);
    virtual void restaurar(Personagem& p);
    virtual bool eDestruivel() const { return true; }
    bool estaMorto() const { return _morto; }

protected:
    int  _durabilidade    = 1;
    int  _durabilidadeMax = 1;
    bool _morto           = false;
};

#endif // MINECIN_MUNDO_PEDRA_H
