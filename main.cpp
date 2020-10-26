#include "window.h"
#include "renderer.h"

int main() {
    auto window = Window::GetInstance();
    auto renderer = Renderer::GetInstance();

    window->Init(800, 600, "OpenGL-Learning", bind(&Renderer::Draw, renderer));
    window->Update();
    window->Shutdown();

    return 0;
}