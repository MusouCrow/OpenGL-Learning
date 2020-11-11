#ifndef RENDER_CAMERA_H
#define RENDER_CAMERA_H

#include <functional>
#include <glm/glm.hpp>
#include "../common.h"
#include "transform.h"

class Camera {
public:
    Camera(int width, int height, function<void()> OnAdjust);
    Camera(int width, int height, float zNear, float zFar, function<void()> OnAdjust);
    Camera(int width, int height, float fov, float zNear, float zFar, function<void()> OnAdjust);
    shared_ptr<Transform> transform;
    glm::mat4 GetView();
    glm::mat4 GetProjection();
    void SetPerspective(float fov, float zNear, float zFar);
    void SetOrtho(float zNear, float zFar);
private:
    float width;
    float height;
    glm::mat4 view;
    glm::mat4 projection;
    function<void()> OnAdjust;
    void AdjustView();
};

#endif