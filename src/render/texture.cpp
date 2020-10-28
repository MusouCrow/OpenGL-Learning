#include <glad/glad.h>
#include "lib/file.h"
#include "texture.h"

Texture::Texture(string path) {
    glGenTextures(1, &this->id); // 创建1个纹理对象

    this->Bind(); // 绑定纹理对象，接下来的纹理操作都会对应它
    this->SetWrap(GL_REPEAT); // 设置围绕方式
    this->SetFilter(GL_NEAREST); // 设置过滤模式
    
    int width, height, channel;
    unsigned char* data = File::ReadImage(path, width, height, channel);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    File::FreeImage(data);
}

Texture::~Texture() {
    if (this->id != 0) {
        glDeleteTextures(1, (GLuint*)&this->id);
    }
}

void Texture::Bind() {
    glBindTexture(GL_TEXTURE_2D, this->id); // 绑定纹理，将会影响Shader的Texture Uniform
}

void Texture::SetWrap(int wrap) {
    if (this->wrap == wrap) {
        return;
    }

    this->wrap = wrap;
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrap);
}

void Texture::SetFilter(int filter) {
    if (this->filter == filter) {
        return;
    }

    this->filter = filter;
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filter);
}

unsigned int Texture::GetId() {
    return this->id;
}

int Texture::GetWrap() {
    return this->wrap;
}

int Texture::GetFilter() {
    return this->filter;
}
