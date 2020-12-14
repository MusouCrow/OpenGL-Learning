#ifndef GUI_H
#define GUI_H

#include <functional>
#include <GLFW/glfw3.h>
#include "common.h"

class Gui {
public:
    static Gui* GetInstance();
    void Init(GLFWwindow* window, function<void()> OnDraw);
    void BeginDraw();
    void EndDraw();
    void Shutdown();
    function<void()> OnDraw;
private:
};

#endif