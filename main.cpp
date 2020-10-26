#include <GL/glew.h>
#include "window.h"
#include "renderer.h"
#include "lib/file.h"

int main() {
    auto window = Window::GetInstance();
    auto renderer = Renderer::GetInstance();

    window->Init(800, 600, "OpenGL-Learning", bind(&Renderer::Draw, renderer));
    // renderer->Init();

    window->Update();
    window->Shutdown();
    
    return 0;
}