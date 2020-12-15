#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <imgui.h>

#include "window.h"
#include "pipeline.h"
#include "gui.h"
#include "lib/file.h"

void Draw() {
    auto pipeline = Pipeline::GetInstance();
    auto gui = Gui::GetInstance();

    gui->BeginDraw();
    pipeline->Draw();
    gui->EndDraw();
}

void UIDraw() {

}

int main() {
    auto window = Window::GetInstance();
    auto pipeline = Pipeline::GetInstance();
    auto gui = Gui::GetInstance();
    
    window->Init(800, 600, "OpenGL-Learning", Draw);
    pipeline->Init(800, 600);
    gui->Init(window->GetFlag(), UIDraw);
    
    window->Update();
    window->Shutdown();
    
    return 0;
}