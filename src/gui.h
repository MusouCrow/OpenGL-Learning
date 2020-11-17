#ifndef GUI_H
#define GUI_H

#include <GLFW/glfw3.h>

class Gui {
public:
    static Gui* GetInstance();
    void Init(GLFWwindow* window);
    void BeginDraw();
    void EndDraw();
    void Shutdown();
private:
};

#endif