#ifndef UTIL_COLOR_H
#define UTIL_COLOR_H

#include "common.h"

struct Color {
    float r;
    float g;
    float b;
    float a;

    Color Mul(float value) {
        return Color {this->r * value, this->g * value, this->b * value, this->a * value};
    }
};

#endif