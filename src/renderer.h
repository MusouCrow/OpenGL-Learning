#ifndef RENDERER_H
#define RENDERER_H

#include <GLFW/glfw3.h>
#include "common.h"

class Renderer {
public:
    static Renderer* GetInstance();
    void Draw();
};

#endif