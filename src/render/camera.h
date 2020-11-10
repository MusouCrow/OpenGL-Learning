#ifndef RENDER_CAMERA_H
#define RENDER_CAMERA_H

#include <functional>
#include <glm/glm.hpp>
#include "../common.h"
#include "transform.h"

class Camera {
public:
    Camera(int width, int height, function<void()> OnAdjust);
    shared_ptr<Transform> transform;
    glm::mat4 GetMatrix();
private:
    glm::mat4 matrix;
    function<void()> OnAdjust;
    void Adjust();
    void AdjustMatrix();
};

#endif