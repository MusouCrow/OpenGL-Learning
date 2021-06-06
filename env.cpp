#include <imgui.h>
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "common.h"
#include "pipeline.h"
#include "times.h"
#include "lib/math.h"
#include "lib/model.h"
#include "lib/file.h"
#include "util/tween.h"
#include "util/tranUnit.hpp"

TranUnit units[3] = {
    {glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(0.0f, 0.0f, 0.0f)}, // Front
    {glm::vec3(2.0f, 0.0f, 0.0f), glm::vec3(0.0f, 90.0f, 0.0f)}, // Left
    {glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(-89.0f, 0.0f, 0.0f)} // Top
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

void SetCamera(TranUnit& unit) {
    auto transform = Pipeline::GetInstance()->camera->transform;
    current = TranUnit {transform->GetPosition(), transform->GetRotate()};
    target = TranUnit {unit.position, unit.rotation};
    tween.Enter(0.0f, 1.0f, 0.7f, Easing::InOutQuad);
}

shared_ptr<Renderer> NewRenderer(string path, shared_ptr<Mesh> mesh, glm::vec3 position, glm::vec3 scale, glm::vec3 rotate) {
    auto renderer = make_shared<Renderer>(mesh, "shader/test", path);
    
    renderer->transform->SetPosition(position);
    renderer->transform->SetScale(scale);
    renderer->transform->SetRotate(rotate);

    return renderer;
}

void Init() {
    auto transform = Pipeline::GetInstance()->camera->transform;
    transform->SetPosition(glm::vec3(0.0f, 0.0f, -2.0f));
    transform->SetRotate(glm::vec3(0.0f, 0.0f, 0.0f));

    auto mesh = Model::NewRectangle();    
    auto pos = glm::vec3();
    auto scale = glm::vec3(0.5f, 0.5f, 0.5f);
    auto rot = glm::vec3(-45.0f, 45.0f, 0.0f);
    auto renderer = NewRenderer("image/wall.jpg", mesh, pos, scale, rot);
    Pipeline::GetInstance()->AddRenderer(renderer);

    Assimp::Importer importer;
    auto path = File::FormatPath("model/box.obj");
    auto scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    auto meshData = scene->mMeshes[0];

    cout << meshData << endl;
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
    
    ImGui::End();
}