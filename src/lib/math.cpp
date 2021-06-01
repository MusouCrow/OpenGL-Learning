#include <random>
#include "math.h"

default_random_engine engine;

float Math::Lerp(float a, float b, float t) {
    if (t <= 0) {
        return a;
    }
    else if (t >= 1) {
        return b;
    }

    return t * b + (1 - t) * a;
}

glm::vec3 Math::Lerp(glm::vec3 a, glm::vec3 b, float t) {
    return glm::vec3(Math::Lerp(a.x, b.x, t), Math::Lerp(a.y, b.y, t), Math::Lerp(a.z, b.z, t));
}

float Math::Random(float a, float b) {
    uniform_real_distribution<float> u(a, b);
    return u(engine);
}