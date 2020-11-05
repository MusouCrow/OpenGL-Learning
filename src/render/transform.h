#ifndef RENDER_TRANSFORM_H
#define RENDER_TRANSFORM_H

#include <functional>
#include <glm/glm.hpp>
#include "common.h"

class Transform {
public:
    Transform(function<void()> OnAdjust);
    glm::vec3 GetPosition();
    glm::vec3 GetScale();
    glm::vec3 GetRotate();
    glm::mat4 GetMatrix();
    void SetPosition(glm::vec3 position);
    void SetScale(glm::vec3 scale);
    void SetRotate(glm::vec3 rotate);
private:
    glm::mat4 matrix;
    glm::vec3 rotation;
    function<void()> OnAdjust;
};

#endif