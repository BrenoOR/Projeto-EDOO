#include "entidades/Personagem.h"
#include "core/AssetsHandler.h"
#include <spdlog/spdlog.h>

Personagem::Personagem(Vect2 posSpawn)
    : _pos(posSpawn), _posSpawn(posSpawn) {}

void Personagem::processarInput(const IInputProvider& input, int indiceJogador) {
    _picaretaAtiva  = false;
    _restaurarAtiva = false;

    Tecla tCima, tBaixo, tEsquerda, tDireita, tMinerar, tRestaurar;
    if (indiceJogador == 0) {
        tCima = Tecla::W;         tBaixo    = Tecla::S;
        tEsquerda = Tecla::A;     tDireita  = Tecla::D;
        tMinerar  = Tecla::F;     tRestaurar = Tecla::G;
    } else {
        tCima = Tecla::Cima;      tBaixo    = Tecla::Baixo;
        tEsquerda = Tecla::Esquerda; tDireita = Tecla::Direita;
        tMinerar  = Tecla::Num0;  tRestaurar = Tecla::Num1;
    }

    Vect2 delta{};
    if (input.isHeld(tCima))     { delta.y -= VELOCIDADE; _facing = Facing::UP;    }
    if (input.isHeld(tBaixo))    { delta.y += VELOCIDADE; _facing = Facing::DOWN;  }
    if (input.isHeld(tEsquerda)) { delta.x -= VELOCIDADE; _facing = Facing::LEFT;  }
    if (input.isHeld(tDireita))  { delta.x += VELOCIDADE; _facing = Facing::RIGHT; }

    if (delta.x != 0.0f || delta.y != 0.0f) {
        aplicarMovimento(delta);
        if (++_contadorAnim >= 3) {
            _frameAnim    = (_frameAnim == 1) ? 2 : 1;
            _contadorAnim = 0;
        }
    }

    if (input.wasPressed(tMinerar)) {
        _picaretaAtiva = true;
        _rectPicareta  = calcularRectPicareta();
    }
    if (input.wasPressed(tRestaurar)) {
        _restaurarAtiva = true;
        _rectPicareta   = calcularRectPicareta();
    }
}

void Personagem::aplicarMovimento(Vect2 delta) {
    _pos += delta;
}

void Personagem::limitarPosicao(Rect lim) {
    if (_pos.x < lim.x)                    _pos.x = lim.x;
    if (_pos.x > lim.right()  - TAMANHO)   _pos.x = lim.right()  - TAMANHO;
    if (_pos.y < lim.y)                    _pos.y = lim.y;
    if (_pos.y > lim.bottom() - TAMANHO)   _pos.y = lim.bottom() - TAMANHO;
}

void Personagem::voltarParaSpawn() {
    spdlog::debug("Personagem::voltarParaSpawn pos=({},{})", _posSpawn.x, _posSpawn.y);
    _pos = _posSpawn;
}

int Personagem::calcularPontuacao() const {
    int pts = (inventario.pedra / 10) * 1
            + inventario.magnetita    * 1
            + inventario.cobre        * 2
            + inventario.ouro         * 5;
    spdlog::debug("calcularPontuacao pts={} mag={} cob={} our={} ped={}",
        pts, inventario.magnetita, inventario.cobre, inventario.ouro, inventario.pedra);
    return pts;
}

Rect Personagem::getLimites() const {
    return { _pos.x, _pos.y, TAMANHO, TAMANHO };
}

Rect Personagem::calcularRectPicareta() const {
    constexpr float OFFSET = 16.0f;
    float x = _pos.x, y = _pos.y;
    switch (_facing) {
        case Facing::UP:    return { x + TAMANHO / 2, y - OFFSET,      1.0f,   OFFSET };
        case Facing::DOWN:  return { x + TAMANHO / 2, y + TAMANHO,     1.0f,   OFFSET };
        case Facing::LEFT:  return { x - OFFSET,      y + TAMANHO / 2, OFFSET, 1.0f   };
        case Facing::RIGHT: return { x + TAMANHO,     y + TAMANHO / 2, OFFSET, 1.0f   };
        default:            return {};
    }
}

void Personagem::carregarFrames(AssetsHandler& assets, int jogador) {
    _corFallback = (jogador == 0) ? Color::blue() : Color::red();
    const auto& sp = assets.sprites();
    for (int f = 0; f < 4; ++f)
        for (int fr = 0; fr < 2; ++fr)
            frames[f][fr] = sp.robo[jogador][f][fr];
}

void Personagem::mostrar(IRenderer& r) const {
    int fi = static_cast<int>(_facing);
    int fr = _frameAnim - 1; // _frameAnim é 1 ou 2, converte para 0/1
    TextureHandle tex = frames[fi][fr];

    Rect dst{_pos.x, _pos.y, TAMANHO, TAMANHO};
    if (tex)
        r.drawTexture(tex, dst);
    else
        r.drawRect(dst, _corFallback);
}
