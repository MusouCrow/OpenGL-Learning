#include <glm/gtc/matrix_transform.hpp>
#include "transform.h"

Transform::Transform(function<void()> OnAdjust) {
    this->matrix = glm::mat4(1.0f);
    this->OnAdjust = OnAdjust;
}

glm::vec3 Transform::GetPosition() {
    auto& m = this->matrix;
    return glm::vec3(m[0][3], m[1][3], m[2][3]);
}

glm::vec3 Transform::GetScale() {
    auto& m = this->matrix;
    return glm::vec3(m[0][0], m[1][1], m[2][2]);
}

glm::vec3 Transform::GetRotate() {
    return this->rotation;
}

glm::mat4 Transform::GetMatrix() {
    return this->matrix;
}

void Transform::SetPosition(glm::vec3 position) {
    this->matrix[3][0] = position.x;
    this->matrix[3][1] = position.y;
    this->matrix[3][2] = position.z;
    this->OnAdjust();
}
