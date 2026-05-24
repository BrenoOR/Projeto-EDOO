#ifndef MINECIN_TIPOS_VECT2_H
#define MINECIN_TIPOS_VECT2_H

#include <cmath>

struct Vect2 {
    float x = 0.0f, y = 0.0f;

    Vect2() = default;
    Vect2(float x, float y) : x(x), y(y) {}

    static Vect2 zero() { return {0.0f, 0.0f}; }

    Vect2 operator+(Vect2 o) const { return {x + o.x, y + o.y}; }
    Vect2 operator-(Vect2 o) const { return {x - o.x, y - o.y}; }
    Vect2 operator*(float s) const { return {x * s, y * s}; }
    Vect2 operator/(float s) const { return {x / s, y / s}; }
    Vect2& operator+=(Vect2 o) { x += o.x; y += o.y; return *this; }
    Vect2& operator-=(Vect2 o) { x -= o.x; y -= o.y; return *this; }
    Vect2& operator*=(float s) { x *= s; y *= s; return *this; }
    bool operator==(Vect2 o) const { return x == o.x && y == o.y; }
    bool operator!=(Vect2 o) const { return !(*this == o); }

    float length() const { return std::sqrt(x * x + y * y); }
    Vect2 normalized() const {
        float len = length();
        return len > 0.0f ? Vect2{x / len, y / len} : Vect2{};
    }
};

#endif // MINECIN_TIPOS_VECT2_H
