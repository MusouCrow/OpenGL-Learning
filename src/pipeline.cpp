#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "pipeline.h"

Pipeline* Pipeline::GetInstance() {
    static Pipeline instance;

    return &instance;
}

void Pipeline::Init(int width, int height) {
    if (!gladLoadGL()) {
        cout << "Glad Load GL Failed!" << endl;
        exit(-1);
    }
    
    this->r = 0.0f;
    this->s = 0.0f;
    this->dir = 1;

    this->camera = make_shared<Camera>(width, height, bind(&Pipeline::OnCameraUpdated, this));
    this->camera->transform->SetPosition(glm::vec3(0.0f, 0.0f, -2.0f));
    this->OnCameraUpdated();

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
}

void Pipeline::Draw() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    for (auto renderer : this->renderers) {
        renderer->Draw();
    }
}

void Pipeline::OnCameraUpdated() {
    auto view = this->camera->GetView();
    auto projection = this->camera->GetProjection();
    
    for (auto renderer : this->renderers) {
        renderer->SetMatrix("View", view);
        renderer->SetMatrix("Projection", projection);
    }
}

void Pipeline::AddRenderer(shared_ptr<Renderer> renderer) {
    auto view = this->camera->GetView();
    auto projection = this->camera->GetProjection();

    renderer->SetMatrix("View", view);
    renderer->SetMatrix("Projection", projection);
    this->renderers.push_back(renderer);
}