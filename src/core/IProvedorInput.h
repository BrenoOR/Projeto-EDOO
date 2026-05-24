#ifndef MINECIN_CORE_IPROVEDORINPUT_H
#define MINECIN_CORE_IPROVEDORINPUT_H

enum class Tecla {
    W, A, S, D, F, G,
    Cima, Baixo, Esquerda, Direita,
    Num0, Num1,
    T, B, Escape
};

class IProvedorInput {
public:
    virtual ~IProvedorInput() = default;
    virtual bool isHeld(Tecla t)     const = 0;
    virtual bool wasPressed(Tecla t) const = 0;
    virtual void poll() = 0;
};

#endif // MINECIN_CORE_IPROVEDORINPUT_H
