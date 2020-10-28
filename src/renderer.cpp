#include <glad/glad.h>
#include "util/array.hpp"
#include "util/color.hpp"
#include "render/mesh.h"
#include "renderer.h"

Renderer* Renderer::GetInstance() {
    static Renderer instance;

    return &instance;
}

Mesh* NewMesh(string path, float x, float y, float w, float h) {
    // 顶点的索引
    int indices[] = {
        0, 1, 3, // first Triangle
        1, 2, 3 // second Triangle
    };

    // 顶点着色器的数据
    float vertices[] = {
        // position     uv
        w, h, 0.0f,  1.0f, 0.0f, // top right
        w, -h, 0.0f,  1.0f, 1.0f, // bottom right
        -w, -h, 0.0f,  0.0f, 1.0f, // bottom left
        -w, h, 0.0f,  0.0, 0.0f // top left
    };

    auto vertices_array = Array<float> {
        vertices,
        sizeof(vertices) / sizeof(float)
    };

    auto indices_array = Array<int> {
        indices,
        sizeof(indices) / sizeof(int)
    };
    
    for (int i = 0; i < vertices_array.count; i += 5) {
        vertices[i] += x;
        vertices[i + 1] += y;
    }

    return new Mesh(vertices_array, indices_array, "shader/test", path);
}

void Renderer::Init(int width, int height) {
    if (!gladLoadGL()) {
        cout << "Glad Load GL Failed!" << endl;
        exit(-1);
    }
    
    glViewport(0, 0, width, height);
    
    this->meshs.push_back(NewMesh("image/container.jpg", -0.5f, 0.0f, 0.4f, 0.4f));
    this->meshs.push_back(NewMesh("image/wall.jpg", 0.5f, 0.0f, 0.4f, 0.4f));
}

void Renderer::Draw() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    for (auto mesh : this->meshs) {
        mesh->Draw();
    }
}