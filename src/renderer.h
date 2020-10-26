#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "common.h"

class Renderer {
public:
    static Renderer* GetInstance();
    void Init();
    void Draw();
private:
    int shader;
};

#endif