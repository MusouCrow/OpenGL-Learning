#include <glm/gtc/matrix_transform.hpp>
#include "transform.h"

Transform::Transform(function<void()> OnAdjust) {
    this->matrix = glm::mat4(1.0f);
    this->position = glm::mat4(1.0f);
    this->scale = glm::mat4(1.0f);
    this->rotation = glm::mat4(1.0f);
    
    this->OnAdjust = OnAdjust;
    this->AdjustDirection();
}

glm::vec3 Transform::GetPosition() {
    auto& m = this->position;
    return glm::vec3(m[3][0], m[3][1], m[3][2]);
}

glm::vec3 Transform::GetScale() {
    auto& m = this->scale;
    return glm::vec3(m[0][0], m[1][1], m[2][2]);
}

glm::vec3 Transform::GetRotate() {
    return this->rotation_val;
}

glm::mat4 Transform::GetMatrix() {
    return this->matrix;
}

glm::vec3 Transform::GetFront() {
    return this->front;
}

glm::vec3 Transform::GetUp() {
    return this->up;
}

glm::vec3 Transform::GetRight() {
    return this->right;
}

void Transform::SetPosition(const glm::vec3& position) {
    this->position = glm::translate(glm::mat4(1.0f), position);
    this->Adjust();
}

void Transform::SetScale(const glm::vec3& scale) {
    this->scale = glm::scale(glm::mat4(1.0f), scale);
    this->Adjust();
}

void Transform::SetRotate(const glm::vec3& rotate) {
    this->rotation_val = rotate;

    this->rotation = glm::mat4(1.0f);
    this->rotation = glm::rotate(this->rotation, glm::radians(rotate.x), glm::vec3(1.0f, 0.0f, 0.0f));
    this->rotation = glm::rotate(this->rotation, glm::radians(rotate.y), glm::vec3(0.0f, 1.0f, 0.0f));
    this->rotation = glm::rotate(this->rotation, glm::radians(rotate.z), glm::vec3(0.0f, 0.0f, 1.0f));
    
    this->Adjust();
}

void Transform::Adjust() {
    this->matrix = this->position * this->scale * this->rotation;
    this->AdjustDirection();

    if (this->OnAdjust != nullptr) {
        this->OnAdjust();
    }
}

void Transform::AdjustDirection() {
    this->front = glm::normalize(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) * this->rotation);
    this->right = glm::normalize(glm::cross(this->front, glm::vec3(0.0f, 1.0f, 0.0f)));
    this->up = glm::normalize(glm::cross(this->right, this->front));
}