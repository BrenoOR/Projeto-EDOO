#ifndef MINECIN_TIPOS_COLOR_H
#define MINECIN_TIPOS_COLOR_H

#include <cstdint>

struct Color {
    uint8_t r = 0, g = 0, b = 0, a = 255;

    Color() = default;
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) : r(r), g(g), b(b), a(a) {}

    static Color white()   { return {255, 255, 255}; }
    static Color black()   { return {0,   0,   0  }; }
    static Color red()     { return {255, 0,   0  }; }
    static Color green()   { return {0,   255, 0  }; }
    static Color blue()    { return {0,   0,   255}; }
    static Color yellow()  { return {255, 255, 0  }; }
    static Color cyan()    { return {0,   255, 255}; }
    static Color magenta() { return {255, 0,   255}; }
};

#endif // MINECIN_TIPOS_COLOR_H
