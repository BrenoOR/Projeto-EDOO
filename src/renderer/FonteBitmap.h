#ifndef MINECIN_RENDERER_FONTEBITMMAP_H
#define MINECIN_RENDERER_FONTEBITMMAP_H

#include "renderer/IRenderer.h"
#include "tipos/Color.h"
#include <string>

// Desenha texto ASCII maiúsculo com fonte bitmap 5×5 via drawRect
void desenharTexto(IRenderer& r, const std::string& txt,
                   float x, float y, float escala, Color cor);

float larguraTexto(const std::string& txt, float escala);

#endif // MINECIN_RENDERER_FONTEBITMMAP_H
