#include <glad/glad.h>
#include "lib/file.h"
#include "base.h"

Renderer::Renderer(shared_ptr<Mesh> mesh, string shader, string image) {
    this->mesh = mesh;
    this->shader = make_shared<Shader>(shader);
    this->texture = make_shared<Texture>(image);
    this->transform = make_shared<Transform>(bind(&Renderer::AdjustMatrix, this));
    
    this->AdjustMatrix();
}

void Renderer::Draw() {
    this->texture->Bind();
    this->shader->Use();
    this->mesh->Draw();
}

void Renderer::AdjustMatrix() {
    auto matrix = this->transform->GetMatrix();
    this->shader->SetMatrix("Model", matrix);
}
