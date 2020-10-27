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

    // 模型的4个顶点（XYZ）
    float vertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };

    // 顶点的索引
    int indices[] = {
        0, 1, 3, // first Triangle
        1, 2, 3 // second Triangle
    };

    auto vertices_array = Array<float> {
        vertices,
        sizeof(vertices) / sizeof(float)
    };

    auto indices_array = Array<int> {
        indices,
        sizeof(indices) / sizeof(int)
    };

    this->p_mesh = make_shared<Mesh>(vertices_array, indices_array, "shader/test");
}

void Renderer::Draw() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    this->p_mesh->Draw();
}