#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "util/array.hpp"
#include "util/color.hpp"
#include "render/mesh.h"
#include "pipeline.h"

Pipeline* Pipeline::GetInstance() {
    static Pipeline instance;

    return &instance;
}

Renderer* NewRenderer(string path, glm::mat4 model) {
    // 顶点的索引
    int indices[] = {
        0, 1, 3, // first Triangle
        1, 2, 3 // second Triangle
    };

    // 顶点着色器的数据
    float vertices[] = {
        // position        uv
        0.5f, 0.5f, 0.0f,  1.0f, 0.0f, // top right
        0.5f, -0.5f, 0.0f,  1.0f, 1.0f, // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, // bottom left
        -0.5f, 0.5f, 0.0f,  0.0, 0.0f // top left
    };

    auto vertices_array = Array<float> {
        vertices,
        sizeof(vertices) / sizeof(float)
    };

    auto indices_array = Array<int> {
        indices,
        sizeof(indices) / sizeof(int)
    };
    
    auto mesh = make_shared<Mesh>(vertices_array, indices_array);
    
    return new Renderer(mesh, "shader/test", path, model);
}

void Pipeline::Init(int width, int height) {
    if (!gladLoadGL()) {
        cout << "Glad Load GL Failed!" << endl;
        exit(-1);
    }
    
    glViewport(0, 0, width, height);
    
    auto model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 1.0f, 0.0f));
    this->renderers.push_back(NewRenderer("image/container.jpg", model));
}

void Pipeline::Draw() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    for (auto mesh : this->renderers) {
        mesh->Draw();
    }
}