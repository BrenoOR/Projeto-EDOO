#ifndef MINECIN_CORE_TELA_H
#define MINECIN_CORE_TELA_H

#include <memory>

class IProvedorInput;
class IRenderer;

class Tela {
public:
    virtual ~Tela() = default;
    // Retorna a próxima tela, ou nullptr para continuar na atual
    virtual std::unique_ptr<Tela> atualizar(float dt, const IProvedorInput& input) = 0;
    virtual void mostrar(IRenderer&) const {}
};

#endif // MINECIN_CORE_TELA_H
