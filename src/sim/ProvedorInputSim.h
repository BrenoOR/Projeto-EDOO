#ifndef MINECIN_SIM_PROVEDORINPUTSIM_H
#define MINECIN_SIM_PROVEDORINPUTSIM_H

#include "core/IProvedorInput.h"
#include <string>
#include <vector>
#include <set>

struct InputFrame {
    int               frame;
    std::set<Tecla>   held;
    std::set<Tecla>   pressed;
};

class ProvedorInputSim : public IProvedorInput {
    std::vector<InputFrame> _frames;
    int                     _frameAtual = 0;
    const InputFrame*       _atual      = nullptr;

    const InputFrame* entradaAtual() const;
public:
    void carregarScript(const std::string& caminho);

    bool isHeld(Tecla t)     const override;
    bool wasPressed(Tecla t) const override;
    void poll()              override;

    int frameAtual() const { return _frameAtual; }
};

#endif // MINECIN_SIM_PROVEDORINPUTSIM_H
