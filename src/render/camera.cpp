#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include "camera.h"

Camera::Camera(int width, int height, function<void()> OnAdjust) {
    new (this)Camera(width, height, 45.0f, 0.1f, 100.0f, OnAdjust);
}

Camera::Camera(int width, int height, float zNear, float zFar, function<void()> OnAdjust) {
    new (this)Camera(width, height, 0.0f, zNear, zFar, OnAdjust);
}

Camera::Camera(int width, int height, float fov, float zNear, float zFar, function<void()> OnAdjust) {
    this->width = width;
    this->height = height;
    glViewport(0, 0, width, height);
    /*
    if (fov == 0.0f) {
        this->SetOrtho(zNear, zFar);
    }
    else {
        this->SetPerspective(fov, zNear, zFar);
    }
    */
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
    this->view = glm::lookAt(pos, pos + this->transform->GetFront(), glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 Camera::GetView() {
    return this->view;
}

glm::mat4 Camera::GetProjection() {
    return this->projection;
}

void Camera::SetPerspective(float fov, float zNear, float zFar) {
    this->projection = glm::perspective(glm::radians(fov), this->width / this->height, zNear, zFar);
    this->OnAdjust();
}

void Camera::SetOrtho(float zNear, float zFar) {
    this->projection = glm::ortho(0.0f, this->width, 0.0f, this->height, zNear, zFar);
    this->OnAdjust();
}