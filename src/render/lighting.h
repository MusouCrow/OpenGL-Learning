#ifndef RENDER_LIGHTING_H
#define RENDER_LIGHTING_H

#include <set>
#include <glm/vec3.hpp>
#include "../common.h"
#include "util/color.hpp"

struct Light {
    glm::vec3 direction;
    Color color;
    float distanceAttenuation;
    float shadowAttenuation;
};

class Lighting {
public:
    Light mainLight;
    set<Light> addtionalLights;
    void Apply();
};

#endif