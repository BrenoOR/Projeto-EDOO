#include <GL/glew.h>
#include "renderer/Janela.h"
#include <spdlog/spdlog.h>
#include <stdexcept>

Janela::Janela(int largura, int altura, const std::string& titulo)
    : _largura(largura), _altura(altura)
{
    if (!glfwInit())
        throw std::runtime_error("glfwInit falhou");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    _janela = glfwCreateWindow(largura, altura, titulo.c_str(), nullptr, nullptr);
    if (!_janela) {
        glfwTerminate();
        throw std::runtime_error("glfwCreateWindow falhou");
    }

    glfwMakeContextCurrent(_janela);
    glfwSwapInterval(1);
    glfwSetFramebufferSizeCallback(_janela, callbackResize);

    glewExperimental = GL_TRUE;
    GLenum glewErr = glewInit();
    if (glewErr != GLEW_OK && glewErr != GLEW_ERROR_NO_GLX_DISPLAY) {
        glfwDestroyWindow(_janela);
        glfwTerminate();
        throw std::runtime_error(
            std::string("glewInit falhou: ") +
            reinterpret_cast<const char*>(glewGetErrorString(glewErr)));
    }
    if (glewErr != GLEW_OK)
        spdlog::warn("glewInit: {} (ignorado)", reinterpret_cast<const char*>(glewGetErrorString(glewErr)));

    glViewport(0, 0, largura, altura);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    spdlog::info("Janela criada {}x{}", largura, altura);
}

Janela::~Janela() {
    if (_janela) glfwDestroyWindow(_janela);
    glfwTerminate();
}

bool Janela::deveFechar() const {
    return glfwWindowShouldClose(_janela);
}

void Janela::trocarBuffers() {
    glfwSwapBuffers(_janela);
}

void Janela::processarEventos() {
    glfwPollEvents();
}

void Janela::callbackResize(GLFWwindow*, int w, int h) {
    glViewport(0, 0, w, h);
}
