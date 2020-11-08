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
    glm::mat4 position;
    glm::mat4 scale;
    glm::mat4 rotation;
    glm::vec3 rotation_val;
    glm::mat4 matrix;
    void Adjust();
    function<void()> OnAdjust;
};

#endif