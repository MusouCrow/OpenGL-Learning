#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

#include "window.h"
#include "pipeline.h"
#include "lib/file.h"

int main() {
    auto window = Window::GetInstance();
    auto pipeline = Pipeline::GetInstance();

    window->Init(800, 600, "OpenGL-Learning", bind(&Pipeline::Draw, pipeline));
    pipeline->Init(800, 600);
    
    window->Update();
    window->Shutdown();
    
    return 0;
}