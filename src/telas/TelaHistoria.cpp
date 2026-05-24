#include "core/IInputProvider.h"
#include "telas/TelaHistoria.h"
#include "telas/TelaInicio.h"
#include "renderer/FonteBitmap.h"
#include <algorithm>

const std::string TelaHistoria::TEXTO =
    "ANO 2147.\n"
    "\n"
    "A TERRA ESGOTA SEUS RECURSOS.\n"
    "DOIS ROBOS DE MINERACAO SAO ENVIADOS\n"
    "AS PROFUNDEZAS EM BUSCA DOS ULTIMOS\n"
    "MINERIOS CONHECIDOS.\n"
    "\n"
    "APENAS UM VOLTARA COM A MAIOR\n"
    "COLHEITA. BOA SORTE!\n"
    "\n"
    "PRESSIONE QUALQUER TECLA PARA PULAR.";

TelaHistoria::TelaHistoria(AssetsHandler& assets, ModoJogo modo, bool simulacao)
    : _assets(assets), _modo(modo), _simulacao(simulacao) {}

std::unique_ptr<Tela> TelaHistoria::atualizar(float dt, const IInputProvider& input) {
    bool concluido = (_charAtual >= (int)TEXTO.size());

    if (!concluido) {
        if ((input.wasPressed(Tecla::T) || input.isHeld(Tecla::T))
         || (input.wasPressed(Tecla::B) || input.isHeld(Tecla::B))
         || (input.wasPressed(Tecla::W) || input.isHeld(Tecla::W))
         || (input.wasPressed(Tecla::Cima) || input.isHeld(Tecla::Cima))
         || (input.wasPressed(Tecla::F) || input.isHeld(Tecla::F))
         || (input.wasPressed(Tecla::Num0) || input.isHeld(Tecla::Num0))) {
            _charAtual = (int)TEXTO.size();
        } else {
            _acumulado += dt;
            int novos = int(_acumulado * CHARS_POR_SEG);
            _acumulado -= float(novos) / CHARS_POR_SEG;
            _charAtual = std::min(_charAtual + novos, (int)TEXTO.size());
        }
    } else {
        _espera += dt;
        if (_espera >= ESPERA_FINAL)
            return std::make_unique<TelaInicio>(_assets, _modo, _simulacao);
    }

    return nullptr;
}

void TelaHistoria::mostrar(IRenderer& r) const {
    r.drawRect({0, 0, 680, 680}, {10, 10, 20});

    std::string visivel = TEXTO.substr(0, _charAtual);
    desenharTexto(r, visivel, 40, 80, 2.5f, {180, 200, 220});
}
