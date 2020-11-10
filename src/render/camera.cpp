#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include "camera.h"

Camera::Camera(int width, int height, function<void()> OnAdjust) {
    glViewport(0, 0, width, height);
    
    this->transform = make_shared<Transform>(bind(&Camera::Adjust, this));
    this->OnAdjust = OnAdjust;
    this->AdjustMatrix();
}

void Camera::Adjust() {
    this->AdjustMatrix();
    this->OnAdjust();
}

void Camera::AdjustMatrix() {
    auto pos = this->transform->GetPosition();
    this->matrix = glm::lookAt(pos, pos + this->transform->GetFront(), glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 Camera::GetMatrix() {
    return this->matrix;
}