#ifndef MINECIN_INPUT_MANIPULADORINPUTGLFW_H
#define MINECIN_INPUT_MANIPULADORINPUTGLFW_H

#include "core/IProvedorInput.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <unordered_set>

class ManipuladorInputGLFW : public IProvedorInput {
    GLFWwindow*                   _janela;
    std::unordered_set<int>       _held;
    std::unordered_set<int>       _pressed;
    std::unordered_set<int>       _pressedBuffer;

    static ManipuladorInputGLFW*  _instancia;
    static void callbackKey(GLFWwindow*, int key, int, int action, int);

public:
    explicit ManipuladorInputGLFW(GLFWwindow* janela);

    bool isHeld(Tecla t)     const override;
    bool wasPressed(Tecla t) const override;
    void poll()              override;

private:
    static int teclaParaGLFW(Tecla t);
};

#endif // MINECIN_INPUT_MANIPULADORINPUTGLFW_H
