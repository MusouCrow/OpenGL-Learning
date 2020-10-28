#include <glad/glad.h>
#include "util/array.hpp"
#include "util/color.hpp"
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
    
    {
        // 顶点的索引
        int indices[] = {
            0, 1, 3, // first Triangle
            1, 2, 3 // second Triangle
        };

        // 模型的顶点（XYZ）
        float vertices[] = {
            0.3f,  0.3f, 0.0f,  // top right
            0.3f, -0.3f, 0.0f,  // bottom right
            -0.3f, -0.3f, 0.0f,  // bottom left
            -0.3f,  0.3f, 0.0f   // top left 
        };

        auto vertices_array = Array<float> {
            vertices,
            sizeof(vertices) / sizeof(float)
        };

        auto indices_array = Array<int> {
            indices,
            sizeof(indices) / sizeof(int)
        };

        for (int i = 0; i < vertices_array.count; i += 3) {
            vertices[i] += 0.5f;
        }

        Color color {0.2f, 0.2f, 1.0f, 1.0f};
        this->meshs.push_back(new Mesh(vertices_array, indices_array, "shader/test", color));
    }
    
    {
        // 模型的顶点（XYZ）
        float vertices[] = {
            -0.3f, -0.3f, 0.0f, // left  
            0.3f, -0.3f, 0.0f, // right 
            0.0f,  0.3f, 0.0f  // top   
        };

        // 顶点的索引
        int indices[] = {
            0, 1, 2, // first Triangle
        };

        auto vertices_array = Array<float> {
            vertices,
            sizeof(vertices) / sizeof(float)
        };

        auto indices_array = Array<int> {
            indices,
            sizeof(indices) / sizeof(int)
        };

        for (int i = 0; i < vertices_array.count; i += 3) {
            vertices[i] -= 0.5f;
        }

        Color color {1.0f, 0.2f, 0.2f, 1.0f};
        this->meshs.push_back(new Mesh(vertices_array, indices_array, "shader/test", color));
    }
}

void Renderer::Draw() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    for (auto mesh : this->meshs) {
        mesh->Draw();
    }
}