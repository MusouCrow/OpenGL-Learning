#include <glad/glad.h>
#include "lib/file.h"
#include "base.h"

Renderer::Renderer(Mesh& mesh, string shader, string image, glm::mat4& model) {
    this->mesh = mesh;
    this->shader = new Shader(shader);
    this->texture = new Texture(image);

    this->shader->SetMatrix("Model", model);
    this->InitVert();
}

void Renderer::InitVert() {
    glGenVertexArrays(1, &this->vao); // 创建1个顶点缓冲对象
    glGenBuffers(1, &this->vbo); // 创建1个顶点缓冲对象
    glGenBuffers(1, &this->ebo); // 创建1个索引缓冲对象

    glBindVertexArray(this->vao); // 绑定VAO，接下来的顶点状态操作都将基于VAO
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo); // 绑定VBO，类型为顶点属性
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo); // 绑定EBO，类型为顶点索引
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->mesh.vertices.count, this->mesh.vertices.list, GL_STATIC_DRAW); // 传入顶点数据到VBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * this->mesh.indices.count, this->mesh.indices.list, GL_STATIC_DRAW); // 传入索引数据到EBO
    
    // 解析传入的顶点数据给着色器使用，VBO → VAO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0); // 坐标
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3)); // UV
    
    // 启用顶点属性
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    // 解除绑定
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Renderer::Draw() {
    this->texture->Bind();
    this->shader->Use();
    
    glBindVertexArray(this->vao); // 绑定VAO，使用相应顶点属性
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo); // 绑定EBO，使用相应顶点索引
    glDrawElements(GL_TRIANGLES, this->mesh.indices.count, GL_UNSIGNED_INT, nullptr); // 绘制由索引组织的面
}
