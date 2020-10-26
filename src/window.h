#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include "common.h"

class Window {
public:
    static Window* GetInstance();
    void Init(int width, int height, string title);
    void Update();
    void Shutdown();
private:
    GLFWwindow* window;
};

#endif