#include <glad/glad.h>
#include "lib/file.h"
#include "stb_image.h"
#include "mesh.h"

int InitTexture(string path) {
    unsigned int texture;
    glGenTextures(1, &texture); // 创建1个纹理对象
    glBindTexture(GL_TEXTURE_2D, texture); // 绑定纹理对象，接下来的纹理操作都会对应它
    
    // 设置围绕方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // 设置过滤模式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    int width, height;
    unsigned char* data = File::ReadImage(path, width, height);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    File::FreeImage(data);

    return texture;
}

Mesh::Mesh(Array<float>& vertices, Array<int>& indices, string shader, string image) {
    this->vertices.Clone(vertices);
    this->indices.Clone(indices);
    
    this->shader.Init(shader);
    
    this->InitVert();

    this->texture = InitTexture(image);
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

void Mesh::Draw() {
    glBindTexture(GL_TEXTURE_2D, this->texture); // 绑定纹理，将会影响Shader的Texture Uniform
    this->shader.Use();
    
    glBindVertexArray(this->vao); // 绑定VAO，使用相应顶点属性
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo); // 绑定EBO，使用相应顶点索引
    glDrawElements(GL_TRIANGLES, this->indices.count, GL_UNSIGNED_INT, nullptr); // 绘制由索引组织的面
}
