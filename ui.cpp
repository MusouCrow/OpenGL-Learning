#include <imgui.h>
#include <glm/glm.hpp>

#include "common.h"
#include "pipeline.h"

void UIDraw() {
    bool opened = true;
    int flag = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize;
    auto pos = ImVec2(0, 0);

    ImGui::Begin("Test", &opened, flag);
    ImGui::SetWindowPos(pos, ImGuiCond_None);

    ImGui::Text("Viewpoint");
    
    if (ImGui::Button("Front")) {
        // auto camera = Pipeline::GetInstance()->camera;
        // camera->transform->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    }

    ImGui::SameLine();
    ImGui::Button("Left");
    ImGui::SameLine();
    ImGui::Button("Top");
    
    ImGui::End();
}