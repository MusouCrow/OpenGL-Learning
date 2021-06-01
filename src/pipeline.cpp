#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "lib/math.h"
#include "util/array.hpp"
#include "util/color.hpp"
#include "render/mesh.h"
#include "pipeline.h"

Pipeline* Pipeline::GetInstance() {
    static Pipeline instance;

    return &instance;
}

Renderer* NewRenderer(string path, glm::vec3 position, glm::vec3 scale, glm::vec3 rotate) {
    // 顶点着色器的数据
    float* vertices = new float[180] {
        // Back face
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right         
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
        // Front face
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
        // Left face
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
        // Right face
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right         
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left     
        // Bottom face
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
        // Top face
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right     
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f  // bottom-left
    };

    auto vertices_array = Array<float> {
        vertices,
        180
    };
    
    auto mesh = make_shared<Mesh>(&vertices_array, nullptr);
    auto renderer = new Renderer(mesh, "shader/test", path);
    
    renderer->transform->SetPosition(position);
    renderer->transform->SetScale(scale);
    renderer->transform->SetRotate(rotate);

    return renderer;
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
    
    for (int i = 0; i < 10; i++) {
        float size = Math::Random(0.2f, 0.5f);

        auto pos = glm::vec3(Math::Random(-0.7f, 0.7f), Math::Random(-0.7f, 0.3f), Math::Random(-0.7f, 0.7f));
        auto scale = glm::vec3(size, size, size);
        auto rot = glm::vec3(Math::Random(-45.0f, 45.0f), Math::Random(-45.0f, 45.0f), Math::Random(-45.0f, 45.0f));

        auto renderer = NewRenderer("image/wall.jpg", pos, scale, rot);
        this->renderers.push_back(renderer);
    }
    
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
    
    for (auto mesh : this->renderers) {
        mesh->Draw();
    }
}

void Pipeline::OnCameraUpdated() {
    auto view = this->camera->GetView();
    auto projection = this->camera->GetProjection();
    
    for (auto mesh : this->renderers) {
        mesh->shader->SetMatrix("View", view);
        mesh->shader->SetMatrix("Projection", projection);
    }
}