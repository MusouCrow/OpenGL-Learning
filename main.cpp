#include "window.h"

int main() {
    auto window = Window::GetInstance();

    window->Init(800, 600, "OpenGL-Learning");
    window->Update();
    window->Shutdown();

    return 0;
}