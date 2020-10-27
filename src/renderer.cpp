#include <glad/glad.h>
#include "util/array.hpp"
#include "render/mesh.h"
#include "renderer.h"

Renderer* Renderer::GetInstance() {
    static Renderer instance;

    return &instance;
}

void Renderer::Init(int width, int height) {
    if (!gladLoadGL()) {
        cout << "Glad Load GL Failed!" << endl;
        exit(-1);
    }
    
    glViewport(0, 0, width, height);

    // 模型的三个顶点（XYZ）
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
        0.5f, -0.5f, 0.0f, // right
        0.0f,  0.5f, 0.0f // top
    };

    auto array = Array<float> {
        vertices,
        sizeof(vertices) / sizeof(float)
    };

    this->p_mesh = make_shared<Mesh>(array, "shader/test");
}

void Renderer::Draw() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    this->p_mesh->Draw();
}