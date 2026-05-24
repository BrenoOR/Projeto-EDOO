#include "renderer/FonteBitmap.h"

// Fonte bitmap 5×5 para ASCII 32–90 (espaço até Z)
// Cada char: 5 linhas, cada linha = uint8_t com 5 bits (MSB=esquerda)
static const uint8_t FONTE[59][5] = {
    {0,0,0,0,0},       // ' ' (32)
    {4,4,4,0,4},       // !
    {10,10,0,0,0},     // "
    {10,31,10,31,10},  // #
    {14,20,14,5,30},   // $
    {17,2,4,8,17},     // %
    {12,18,12,19,14},  // &
    {4,4,0,0,0},       // '
    {6,8,8,8,6},       // (
    {12,2,2,2,12},     // )
    {0,10,4,10,0},     // *
    {0,4,14,4,0},      // +
    {0,0,0,4,8},       // ,
    {0,0,14,0,0},      // -
    {0,0,0,0,4},       // .
    {1,2,4,8,16},      // /
    {14,17,17,17,14},  // 0
    {4,12,4,4,14},     // 1
    {14,1,14,16,31},   // 2
    {14,1,6,1,14},     // 3
    {17,17,31,1,1},    // 4
    {31,16,30,1,30},   // 5
    {14,16,30,17,14},  // 6
    {31,1,2,4,4},      // 7
    {14,17,14,17,14},  // 8
    {14,17,15,1,14},   // 9
    {0,4,0,4,0},       // :
    {0,4,0,4,8},       // ;
    {2,4,8,4,2},       // <
    {0,31,0,31,0},     // =
    {8,4,2,4,8},       // >
    {14,1,6,0,4},      // ?
    {14,19,21,19,14},  // @
    {14,17,31,17,17},  // A
    {30,17,30,17,30},  // B
    {14,16,16,16,14},  // C
    {28,18,17,18,28},  // D
    {31,16,30,16,31},  // E
    {31,16,30,16,16},  // F
    {14,16,23,17,14},  // G
    {17,17,31,17,17},  // H
    {14,4,4,4,14},     // I
    {7,1,1,17,14},     // J
    {17,18,28,18,17},  // K
    {16,16,16,16,31},  // L
    {17,27,21,17,17},  // M
    {17,25,21,19,17},  // N
    {14,17,17,17,14},  // O
    {30,17,30,16,16},  // P
    {14,17,21,18,13},  // Q
    {30,17,30,18,17},  // R
    {15,16,14,1,30},   // S
    {31,4,4,4,4},      // T
    {17,17,17,17,14},  // U
    {17,17,17,10,4},   // V
    {17,17,21,27,17},  // W
    {17,10,4,10,17},   // X
    {17,10,4,4,4},     // Y
    {31,2,4,8,31},     // Z
};

static const uint8_t* glifo(char c) {
    int idx = (int)c - 32;
    if (idx < 0 || idx >= 59) idx = 0; // substitui desconhecidos por espaço
    return FONTE[idx];
}

void desenharTexto(IRenderer& r, const std::string& txt,
                   float x, float y, float escala, Color cor) {
    float px = x;
    for (char c : txt) {
        if (c == '\n') { px = x; y += (5 + 2) * escala; continue; }
        char up = (c >= 'a' && c <= 'z') ? (c - 32) : c;
        const uint8_t* g = glifo(up);
        for (int row = 0; row < 5; ++row)
            for (int col = 0; col < 5; ++col)
                if (g[row] & (0x10 >> col))
                    r.drawRect({px + col*escala, y + row*escala, escala, escala}, cor);
        px += (5 + 1) * escala;
    }
}

float larguraTexto(const std::string& txt, float escala) {
    return txt.size() * (5 + 1) * escala;
}
