#include <glad/glad.h>
#include "lib/file.h"
#include "mesh.h"

Mesh::Mesh(Array<float>& vertices, string shader) {
    this->vertices.Clone(vertices);
    this->shader.Init(shader);
    
    this->InitVert();
}

void Mesh::InitVert() {
    glGenVertexArrays(1, &this->vao); // 创建1个顶点缓冲对象
    glGenBuffers(1, &this->vbo); // 创建1个顶点缓冲对象

    glBindVertexArray(this->vao); // 绑定VAO，接下来的顶点状态操作都将基于VAO
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo); // 绑定VBO，类型为顶点属性
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->vertices.count, this->vertices.list, GL_STATIC_DRAW); // 传入顶点数据到VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr); // 解析传入的顶点数据给着色器使用，VBO → VAO
    glEnableVertexAttribArray(0); // 启用第0位顶点属性

    // 解除绑定VAO与VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::Draw() {
    glUseProgram(this->shader.GetId()); // 调用着色器
    glBindVertexArray(this->vao); // 绑定VAO，使用相应顶点属性
    glDrawArrays(GL_TRIANGLES, 0, 3); // 绘制三个顶点组成的面
}
