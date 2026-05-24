#ifndef MINECIN_INPUT_INPUTGLFWHANDLER_H
#define MINECIN_INPUT_INPUTGLFWHANDLER_H

#include "core/IInputProvider.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <unordered_set>

class InputGLFWHandler : public IInputProvider {
    GLFWwindow*                   _janela;
    std::unordered_set<int>       _held;
    std::unordered_set<int>       _pressed;
    std::unordered_set<int>       _pressedBuffer;

    static InputGLFWHandler*  _instancia;
    static void callbackKey(GLFWwindow*, int key, int, int action, int);

public:
    explicit InputGLFWHandler(GLFWwindow* janela);

    bool isHeld(Tecla t)     const override;
    bool wasPressed(Tecla t) const override;
    void poll()              override;

private:
    static int teclaParaGLFW(Tecla t);
};

#endif // MINECIN_INPUT_INPUTGLFWHANDLER_H
