#ifndef WINDOW_H
#define WINDOW_H

#include <functional>
#include <GLFW/glfw3.h>
#include "common.h"

class Window {
public:
    static Window* GetInstance();
    void Init(int width, int height, string title, function<void()> OnTick);
    void Update();
    void Shutdown();
    GLFWwindow* GetFlag();
    function<void()> OnTick;
private:
    GLFWwindow* window;
};

#endif