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
    glm::vec3 GetFront();
    glm::vec3 GetUp();
    glm::vec3 GetRight();
    void SetPosition(glm::vec3 position);
    void SetScale(glm::vec3 scale);
    void SetRotate(glm::vec3 rotate);
private:
    glm::mat4 position;
    glm::mat4 scale;
    glm::mat4 rotation;
    glm::vec3 rotation_val;
    glm::mat4 matrix;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    void Adjust();
    void AdjustDirection();
    function<void()> OnAdjust;
};

#endif