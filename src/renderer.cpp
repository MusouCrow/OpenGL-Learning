#include "renderer.h"

Renderer* Renderer::GetInstance() {
    static Renderer instance;

    return &instance;
}

void Renderer::Draw() {
    glClear(GL_COLOR_BUFFER_BIT);
}