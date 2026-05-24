#ifndef MINECIN_CORE_IINPUTPROVIDER_H
#define MINECIN_CORE_IINPUTPROVIDER_H

enum class Tecla {
    W, A, S, D, F, G,
    Cima, Baixo, Esquerda, Direita,
    Num0, Num1,
    T, B, Escape, Enter
};

class IInputProvider {
public:
    virtual ~IInputProvider() = default;
    virtual bool isHeld(Tecla t)     const = 0;
    virtual bool wasPressed(Tecla t) const = 0;
    virtual void poll() = 0;
};

#endif // MINECIN_CORE_IINPUTPROVIDER_H
