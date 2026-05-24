#ifndef MINECIN_ENTIDADES_PERSONAGEM_H
#define MINECIN_ENTIDADES_PERSONAGEM_H

#include "tipos/Vect2.h"
#include "tipos/Rect.h"
#include "renderer/IRenderer.h"
#include "enums/Facing.h"
#include "core/IProvedorInput.h"

struct Inventario {
    int magnetita = 0;
    int cobre     = 0;
    int ouro      = 0;
    int pedra     = 0;
};

class Personagem {
public:
    static constexpr float VELOCIDADE = 5.0f;
    static constexpr float TAMANHO    = 26.0f;

    int danoPicareta = 1;
    Inventario inventario;
    TextureHandle frames[4][2]{};

    explicit Personagem(Vect2 posSpawn);

    void processarInput(const IProvedorInput& input, int indiceJogador);
    void aplicarMovimento(Vect2 delta);
    void limitarPosicao(Rect limitesMundo);
    void voltarParaSpawn();
    int  calcularPontuacao() const;

    Rect   getLimites()       const;
    Rect   getRectPicareta()  const { return _rectPicareta;  }
    bool   isPicaretaAtiva()  const { return _picaretaAtiva; }
    bool   isRestaurarAtiva() const { return _restaurarAtiva;}
    Facing getFacing()        const { return _facing;        }

    void mostrar(IRenderer& r) const;

private:
    Vect2  _pos;
    Vect2  _posSpawn;
    Facing _facing        = Facing::UP;
    int    _contadorAnim  = 0;
    int    _frameAnim     = 1;
    bool   _picaretaAtiva  = false;
    bool   _restaurarAtiva = false;
    Rect   _rectPicareta;

    Rect calcularRectPicareta() const;
};

#endif // MINECIN_ENTIDADES_PERSONAGEM_H
