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
    bool my_tool_active;
    float my_color[4];

    // Create a window called "My First Tool", with a menu bar.
    ImGui::Begin("My First Tool", &my_tool_active, ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
            if (ImGui::MenuItem("Save", "Ctrl+S"))   { /* Do stuff */ }
            if (ImGui::MenuItem("Close", "Ctrl+W"))  { my_tool_active = false; }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    // Edit a color (stored as ~4 floats)
    ImGui::ColorEdit4("Color", my_color);

    // Plot some values
    const float my_values[] = { 0.2f, 0.1f, 1.0f, 0.5f, 0.9f, 2.2f };
    ImGui::PlotLines("Frame Times", my_values, IM_ARRAYSIZE(my_values));

    // Display contents in a scrolling region
    ImGui::TextColored(ImVec4(1,1,0,1), "Important Stuff");
    ImGui::BeginChild("Scrolling");
    for (int n = 0; n < 50; n++)
        ImGui::Text("%04d: Some text", n);
    ImGui::EndChild();
    ImGui::End();
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