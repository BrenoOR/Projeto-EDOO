#ifndef MINECIN_RENDERER_JANELA_H
#define MINECIN_RENDERER_JANELA_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <string>

class Janela {
    GLFWwindow* _janela = nullptr;
    int         _largura;
    int         _altura;
public:
    Janela(int largura, int altura, const std::string& titulo);
    ~Janela();

    Janela(const Janela&)            = delete;
    Janela& operator=(const Janela&) = delete;

    bool deveFechar() const;
    void trocarBuffers();
    void processarEventos();

    GLFWwindow* ptr()     const { return _janela; }
    int         largura() const { return _largura; }
    int         altura()  const { return _altura;  }

private:
    static void callbackResize(GLFWwindow*, int w, int h);
};

#endif // MINECIN_RENDERER_JANELA_H
