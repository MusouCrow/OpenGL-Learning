#include "base.h"

Renderer::Renderer(shared_ptr<Model> model, string shader, string image) {
    this->model = model;
    this->shader = make_shared<Shader>(shader);
    this->texture = make_shared<Texture>(image);
    this->transform = make_shared<Transform>(bind(&Renderer::AdjustMatrix, this));
    
    this->AdjustMatrix();
}

void Renderer::Draw() {
    this->texture->Bind();
    this->shader->Use();

    for (int i = 0; i < this->model->meshes.size(); i++) {
        this->model->meshes[i]->Draw();
    }
}

void Renderer::AdjustMatrix() {
    auto matrix = this->transform->GetMatrix();
    this->shader->SetMatrix("Model", matrix);
}
