#include <glad/glad.h>
#include "lib/file.h"
#include "shader.h"

Shader::Shader() {}

Shader::Shader(string path) {
    this->Init(path);
}

Shader::~Shader() {
    if (this->id != 0) {
        glDeleteProgram(this->id);
    }
}

void Shader::Init(string path) {
    string vert_src = File::ReadFile(path + ".vs");
    string frag_src = File::ReadFile(path + ".fs");

    int vert_shader = glCreateShader(GL_VERTEX_SHADER);
    int frag_shader = glCreateShader(GL_FRAGMENT_SHADER);

    this->Compile(vert_shader, vert_src);
    this->Compile(frag_shader, frag_src);
    
    this->id = glCreateProgram();
    glAttachShader(this->id, vert_shader);
    glAttachShader(this->id, frag_shader);
    glLinkProgram(this->id);

    int success;
    char log[512];
    glGetProgramiv(this->id, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(this->id, 512, nullptr, log);
        cout << "Shader Link Error: " << log << endl;
    }
    
    glDeleteShader(vert_shader);
    glDeleteShader(frag_shader);
}

int Shader::GetId() {
    return this->id;
}

void Shader::SetColor(string name, Color& color) {
    glUseProgram(this->id);
        int location = glGetUniformLocation(this->id, name.c_str());
        glUniform4f(location, color.r, color.g, color.b, color.a);
    glUseProgram(0);
}

void Shader::Compile(int shader, string& src) {
    const char* code = src.c_str();

    glShaderSource(shader, 1, &code, nullptr);
    glCompileShader(shader);

    int success;
    char log[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, log);
        cout << "Shader Compile Error: " << log << endl;
    }
}
