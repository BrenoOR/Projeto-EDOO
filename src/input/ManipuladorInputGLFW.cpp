#include "input/ManipuladorInputGLFW.h"

ManipuladorInputGLFW* ManipuladorInputGLFW::_instancia = nullptr;

ManipuladorInputGLFW::ManipuladorInputGLFW(GLFWwindow* janela)
    : _janela(janela)
{
    _instancia = this;
    glfwSetKeyCallback(janela, callbackKey);
}

void ManipuladorInputGLFW::callbackKey(GLFWwindow*, int key, int, int action, int) {
    if (!_instancia) return;
    if (action == GLFW_PRESS) {
        _instancia->_held.insert(key);
        _instancia->_pressedBuffer.insert(key);
    } else if (action == GLFW_RELEASE) {
        _instancia->_held.erase(key);
    }
}

int ManipuladorInputGLFW::teclaParaGLFW(Tecla t) {
    switch (t) {
        case Tecla::W:        return GLFW_KEY_W;
        case Tecla::A:        return GLFW_KEY_A;
        case Tecla::S:        return GLFW_KEY_S;
        case Tecla::D:        return GLFW_KEY_D;
        case Tecla::F:        return GLFW_KEY_F;
        case Tecla::G:        return GLFW_KEY_G;
        case Tecla::Cima:     return GLFW_KEY_UP;
        case Tecla::Baixo:    return GLFW_KEY_DOWN;
        case Tecla::Esquerda: return GLFW_KEY_LEFT;
        case Tecla::Direita:  return GLFW_KEY_RIGHT;
        case Tecla::Num0:     return GLFW_KEY_KP_0;
        case Tecla::Num1:     return GLFW_KEY_KP_1;
        case Tecla::T:        return GLFW_KEY_T;
        case Tecla::B:        return GLFW_KEY_B;
        case Tecla::Escape:   return GLFW_KEY_ESCAPE;
        default:              return -1;
    }
}

bool ManipuladorInputGLFW::isHeld(Tecla t) const {
    return _held.count(teclaParaGLFW(t)) > 0;
}

bool ManipuladorInputGLFW::wasPressed(Tecla t) const {
    return _pressed.count(teclaParaGLFW(t)) > 0;
}

void ManipuladorInputGLFW::poll() {
    _pressed = std::move(_pressedBuffer);
    _pressedBuffer.clear();
}
