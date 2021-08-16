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

auto lightTransform = Transform(nullptr);

void SetCamera(TranUnit& unit) {
    auto transform = Pipeline::GetInstance()->camera->transform;
    current = TranUnit {transform->GetPosition(), transform->GetRotate()};
    target = TranUnit {unit.position, unit.rotation};
    tween.Enter(0.0f, 1.0f, 0.7f, Easing::InOutQuad);
}

shared_ptr<Renderer> NewRenderer(string prefabPath) {
    auto prefab = Resource::LoadPrefab(prefabPath);

    auto renderer = make_shared<Renderer>(prefab->model, prefab->materials);
    renderer->transform->SetPosition(prefab->position);
    renderer->transform->SetScale(prefab->scale);
    renderer->transform->SetRotate(prefab->rotation);
    Pipeline::GetInstance()->AddRenderer(renderer);

    return renderer;
}

void Init() {
    auto transform = Pipeline::GetInstance()->camera->transform;
    transform->SetPosition(glm::vec3(0.0f, 0.0f, -5.0f));
    transform->SetRotate(glm::vec3(0.0f, 0.0f, 0.0f));

    NewRenderer("nanosuit");
    NewRenderer("box");
    
    Resource::Log();

    lightTransform.SetRotate(glm::vec3(0, 175, 0));
    auto lighting = Pipeline::GetInstance()->lighting;
    lighting->mainLight.color = Color {2, 1, 1, 1};
    lighting->mainLight.direction = lightTransform.GetFront();
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
        ImGui::Text("Rotation");
        
        auto lighting = Pipeline::GetInstance()->lighting;
        auto rotation = lightTransform.GetRotate();

        if (ImGui::DragFloat3("", (float*)&rotation)) {
            lightTransform.SetRotate(rotation);
            lighting->mainLight.direction = lightTransform.GetFront();
        }

        ImGui::Text("Color");
        ImGui::ColorEdit3("", (float*)&lighting->mainLight.color, ImGuiColorEditFlags_HDR);
    }

    ImGui::End();
}