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

Renderer* NewRenderer(string path, glm::vec3 position, glm::vec3 scale, glm::vec3 rotate) {
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
    
    glViewport(0, 0, width, height);
    
    this->renderers.push_back(NewRenderer("image/container.jpg", glm::vec3(0.5f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(45.0f, 45.0f, 0.0f)));
    this->renderers.push_back(NewRenderer("image/wall.jpg", glm::vec3(-0.5f, 0.1f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 45.0f)));
}

void Pipeline::Draw() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    for (auto mesh : this->renderers) {
        mesh->Draw();
    }
}