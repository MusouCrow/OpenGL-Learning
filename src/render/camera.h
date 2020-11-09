#ifndef RENDER_CAMERA_H
#define RENDER_CAMERA_H

#include <glm/glm.hpp>
#include "common.h"
#include "transform.h"

class Camera {
public:
    Camera();
private:
    shared_ptr<Transform> transform;
};

#endif