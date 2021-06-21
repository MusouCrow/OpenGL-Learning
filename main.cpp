#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window.h"
#include "pipeline.h"
#include "gui.h"
#include "env.cpp"

void Init();
void Update();

void Tick() {
    auto pipeline = Pipeline::GetInstance();
    auto gui = Gui::GetInstance();

    Update();

    gui->BeginDraw();
    pipeline->Draw();
    gui->EndDraw();
}

int main() {
    auto window = Window::GetInstance();
    auto pipeline = Pipeline::GetInstance();
    auto gui = Gui::GetInstance();
    
    window->Init(800, 600, "OpenGL-Learning", Tick);
    pipeline->Init(800, 600);
    gui->Init(window->GetFlag(), UIDraw);

    Init();
    
    window->Update();
    window->Shutdown();
    
    return 0;
}