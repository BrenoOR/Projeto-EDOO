#include "sim/InputSimProvider.h"
#include <json/json.h>
#include <fstream>
#include <stdexcept>
#include <map>

static const std::map<std::string, Tecla> MAPA_TECLAS = {
    {"W",        Tecla::W},
    {"A",        Tecla::A},
    {"S",        Tecla::S},
    {"D",        Tecla::D},
    {"F",        Tecla::F},
    {"G",        Tecla::G},
    {"Cima",     Tecla::Cima},
    {"Baixo",    Tecla::Baixo},
    {"Esquerda", Tecla::Esquerda},
    {"Direita",  Tecla::Direita},
    {"Num0",     Tecla::Num0},
    {"Num1",     Tecla::Num1},
    {"T",        Tecla::T},
    {"B",        Tecla::B},
    {"Escape",   Tecla::Escape},
};

static Tecla teclaDeString(const std::string& s) {
    auto it = MAPA_TECLAS.find(s);
    if (it == MAPA_TECLAS.end())
        throw std::runtime_error("Tecla desconhecida no script: " + s);
    return it->second;
}

void InputSimProvider::carregarScript(const std::string& caminho) {
    std::ifstream arquivo(caminho);
    if (!arquivo)
        throw std::runtime_error("Nao foi possivel abrir o script: " + caminho);

    Json::Value raiz;
    Json::CharReaderBuilder builder;
    std::string erros;
    if (!Json::parseFromStream(builder, arquivo, &raiz, &erros))
        throw std::runtime_error("Erro ao parsear JSON: " + erros);

    _frames.clear();
    for (const auto& entrada : raiz["frames"]) {
        InputFrame f;
        f.frame = entrada["frame"].asInt();
        for (const auto& t : entrada["held"])
            f.held.insert(teclaDeString(t.asString()));
        for (const auto& t : entrada["pressed"])
            f.pressed.insert(teclaDeString(t.asString()));
        _frames.push_back(std::move(f));
    }

    _frameAtual = 0;
    _atual      = entradaAtual();
}

const InputFrame* InputSimProvider::entradaAtual() const {
    const InputFrame* candidato = nullptr;
    for (const auto& f : _frames) {
        if (f.frame <= _frameAtual)
            candidato = &f;
        else
            break;
    }
    return candidato;
}

bool InputSimProvider::isHeld(Tecla t) const {
    return _atual && _atual->held.count(t) > 0;
}

bool InputSimProvider::wasPressed(Tecla t) const {
    if (!_atual || _atual->frame != _frameAtual)
        return false;
    return _atual->pressed.count(t) > 0;
}

void InputSimProvider::poll() {
    ++_frameAtual;
    _atual = entradaAtual();
}
