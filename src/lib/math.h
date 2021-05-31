#ifndef LIB_MATH_H
#define LIB_MATH_H

#include <glm/glm.hpp>
#include "../common.h"

class Math {
public:
    static float Lerp(float a, float b, float t);
    static glm::vec3 Lerp(glm::vec3 a, glm::vec3 b, float t);
};

#endif