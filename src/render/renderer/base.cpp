#include "base.h"

Renderer::Renderer(shared_ptr<Model> model, vector<shared_ptr<Material>> materials) {
    this->model = model;
    this->materials = materials;
    this->transform = make_shared<Transform>(bind(&Renderer::AdjustMatrix, this));
    this->AdjustMatrix();
}

void Renderer::Draw() {
    for (int i = 0; i < this->model->meshes.size(); i++) {
        this->materials[i]->Bind();
        this->model->meshes[i]->Draw();
    }
}

void Renderer::SetMatrix(string name, glm::mat4& matrix) {
    for (auto material : materials) {
        material->GetShader()->SetValue(name, matrix);
    }
}

void Renderer::AdjustMatrix() {
    auto matrix = this->transform->GetMatrix();
    this->SetMatrix("Model", matrix);
}