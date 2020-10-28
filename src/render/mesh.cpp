#include <glad/glad.h>
#include "lib/file.h"
#include "mesh.h"

Mesh::Mesh(Array<float>& vertices, Array<int>& indices, string shader, Color& color) {
    this->vertices.Clone(vertices);
    this->indices.Clone(indices);
    
    this->shader.Init(shader);
    this->shader.SetColor("outColor", color);
    
    this->InitVert();
}

Mesh::~Mesh() {
    delete[] this->vertices.list;
    delete[] this->indices.list;
}

void Mesh::InitVert() {
    glGenVertexArrays(1, &this->vao); // 创建1个顶点缓冲对象
    glGenBuffers(1, &this->vbo); // 创建1个顶点缓冲对象
    glGenBuffers(1, &this->ebo); // 创建1个索引缓冲对象

    glBindVertexArray(this->vao); // 绑定VAO，接下来的顶点状态操作都将基于VAO
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo); // 绑定VBO，类型为顶点属性
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo); // 绑定EBO，类型为顶点索引

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->vertices.count, this->vertices.list, GL_STATIC_DRAW); // 传入顶点数据到VBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * this->indices.count, this->indices.list, GL_STATIC_DRAW); // 传入索引数据到EBO
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr); // 解析传入的顶点数据给着色器使用，VBO → VAO
    glEnableVertexAttribArray(0); // 启用第0位顶点属性
    
    // 解除绑定
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::Draw() {
    this->shader.Use();
    
    glBindVertexArray(this->vao); // 绑定VAO，使用相应顶点属性
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo); // 绑定EBO，使用相应顶点索引
    glDrawElements(GL_TRIANGLES, this->indices.count, GL_UNSIGNED_INT, nullptr); // 绘制由索引组织的面
}
