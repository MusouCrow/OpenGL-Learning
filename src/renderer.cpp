#include "renderer.h"

void InitDraw(float vertices[], int count) {
    unsigned int vao; // 顶点数组对象，索引顶点各种属性
    unsigned int vbo; // 顶点缓冲对象，索引显存的顶点数据

    glGenVertexArrays(1, &vao); // 创建1个顶点缓冲对象
    glGenBuffers(1, &vbo); // 创建1个顶点缓冲对象

    glBindVertexArray(vao); // 绑定vao，接下来的顶点状态操作都将基于vao
    glBindBuffer(GL_ARRAY_BUFFER, vbo); // 绑定vbo，类型为顶点属性

    glBufferData(GL_ARRAY_BUFFER, sizeof(*vertices) * count, vertices, GL_STATIC_DRAW); // 传入顶点数据到vbo
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr); // 解析传入的顶点数据给着色器使用

    // 解除绑定vao与vbo
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Renderer* Renderer::GetInstance() {
    static Renderer instance;

    return &instance;
}

void Renderer::Init() {
    // 模型的三个顶点（XYZ）
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
        0.5f, -0.5f, 0.0f, // right
        0.0f,  0.5f, 0.0f // top
    };

    InitDraw(vertices, sizeof(vertices) / sizeof(float));
}

void Renderer::Draw() {
    glClear(GL_COLOR_BUFFER_BIT);
}