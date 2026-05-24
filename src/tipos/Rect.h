#ifndef MINECIN_TIPOS_RECT_H
#define MINECIN_TIPOS_RECT_H

#include "Vect2.h"

struct Rect {
    float x = 0.0f, y = 0.0f, w = 0.0f, h = 0.0f;

    Rect() = default;
    Rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}

    float right()  const { return x + w; }
    float bottom() const { return y + h; }
    Vect2 center() const { return {x + w * 0.5f, y + h * 0.5f}; }

    bool contains(Vect2 p) const {
        return p.x >= x && p.x <= right() && p.y >= y && p.y <= bottom();
    }
    bool intersects(const Rect& o) const {
        return x < o.right() && right() > o.x && y < o.bottom() && bottom() > o.y;
    }
};

#endif // MINECIN_TIPOS_RECT_H
