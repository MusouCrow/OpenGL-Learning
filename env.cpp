#include <vector>
#include <imgui.h>
#include <glm/glm.hpp>

#include "common.h"
#include "pipeline.h"
#include "times.h"
#include "lib/math.h"
#include "lib/resource.h"
#include "util/tween.h"
#include "util/tranUnit.hpp"
#include "render/material.h"

TranUnit units[3] = {
    {glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f, 0.0f, 0.0f)}, // Front
    {glm::vec3(5.0f, 0.0f, 0.0f), glm::vec3(0.0f, 90.0f, 0.0f)}, // Left
    {glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(-89.0f, 0.0f, 0.0f)} // Top
};

TranUnit current = TranUnit();
TranUnit target = TranUnit();

Tween tween = Tween([]() {
    float rate = tween.GetRate();
    
    auto pos = Math::Lerp(current.position, target.position, rate);
    auto rot = Math::Lerp(current.rotation, target.rotation, rate);
    auto transform = Pipeline::GetInstance()->camera->transform;

    transform->SetPosition(pos);
    transform->SetRotate(rot);
});

auto lightDir = glm::vec3(0, -1, 0);
auto lightColor = Color {2, 1, 1, 1};

void SetCamera(TranUnit& unit) {
    auto transform = Pipeline::GetInstance()->camera->transform;
    current = TranUnit {transform->GetPosition(), transform->GetRotate()};
    target = TranUnit {unit.position, unit.rotation};
    tween.Enter(0.0f, 1.0f, 0.7f, Easing::InOutQuad);
}

shared_ptr<Renderer> NewRenderer(shared_ptr<Prefab> prefab) {
    auto renderer = make_shared<Renderer>(prefab->model, prefab->materials);
    renderer->transform->SetPosition(prefab->position);
    renderer->transform->SetScale(prefab->scale);
    renderer->transform->SetRotate(prefab->rotation);

    return renderer;
}

void Init() {
    auto transform = Pipeline::GetInstance()->camera->transform;
    transform->SetPosition(glm::vec3(0.0f, 0.0f, -5.0f));
    transform->SetRotate(glm::vec3(0.0f, 0.0f, 0.0f));

    auto prefab = Resource::LoadPrefab("nanosuit");
    auto renderer = NewRenderer(prefab);
    Pipeline::GetInstance()->AddRenderer(renderer);
    Resource::Log();

    Shader::SetGlobalVector3("_LightDir", lightDir);
    Shader::SetGlobalColor("_LightColor", lightColor);
}

void Update() {
    float dt = Time::GetInstance()->GetDeltaTime();
    tween.Update(dt);
}

void UIDraw() {
    bool opened = true;
    int flag = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize;
    auto pos = ImVec2(0, 0);

    ImGui::Begin("Test", &opened, flag);
    ImGui::SetWindowPos(pos, ImGuiCond_None);

    int fps = Time::GetInstance()->GetFPS();
    ImGui::Text("FPS: %d", fps);

    ImGui::Text("Viewpoint");
    
    if (ImGui::Button("Front")) {
        SetCamera(units[0]);
    }

    ImGui::SameLine();
    
    if (ImGui::Button("Left")) {
        SetCamera(units[1]);
    }

    ImGui::SameLine();

    if (ImGui::Button("Top")) {
        SetCamera(units[2]);
    }

    ImGui::Separator();

    if (ImGui::CollapsingHeader("Light")) {
        ImGui::Text("Direction");
        if (ImGui::DragFloat3("", (float*)&lightDir)) {
            Shader::SetGlobalVector3("_LightDir", lightDir);
        }

        ImGui::Text("Color");
        if (ImGui::ColorEdit3("", (float*)&lightColor, ImGuiColorEditFlags_HDR)) {
            Shader::SetGlobalColor("_LightColor", lightColor);
        }
    }

    ImGui::End();
}