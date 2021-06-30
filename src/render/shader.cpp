#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include "lib/file.h"
#include "shader.h"

Shader::Shader(string& vert_src, string& frag_src) {
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

Shader::~Shader() {
    if (this->id != 0) {
        glDeleteProgram(this->id);
    }
}

int Shader::GetId() {
    return this->id;
}

int Shader::GetLocation(string name) {
    return glGetUniformLocation(this->id, name.c_str());
}

void Shader::Use() {
    glUseProgram(this->id);
}

void Shader::SetInt(string name, int value) {
    this->Use();
    int location = this->GetLocation(name);
    glUniform1i(location, value);
}

void Shader::SetFloat(string name, float value) {
    this->Use();
    int location = this->GetLocation(name);
    glUniform1f(location, value);
}

void Shader::SetColor(string name, Color& color) {
    this->Use();
    int location = this->GetLocation(name);
    glUniform4f(location, color.r, color.g, color.b, color.a);
}

void Shader::SetMatrix(string name, glm::mat4& matrix) {
    this->Use();
    int location = this->GetLocation(name);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::SetVector3(string name, glm::vec3& vector) {
    this->Use();
    int location = this->GetLocation(name);
    glUniform3f(location, vector.x, vector.y, vector.z);
}

void Shader::SetVector4(string name, glm::vec4& vector) {
    this->Use();
    int location = this->GetLocation(name);
    glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
}

int Shader::GetInt(string name) {
    this->Use();
    int location = this->GetLocation(name);
    
    int value;
    glGetUniformiv(this->id, location, &value);
    
    return value;
}

float Shader::GetFloat(string name) {
    this->Use();
    int location = this->GetLocation(name);

    float value;
    glGetUniformfv(this->id, location, &value);
    
    return value;
}

Color Shader::GetColor(string name) {
    this->Use();
    int location = this->GetLocation(name);

    Color color;
    glGetUniformfv(this->id, location, (float*)&color);
    
    return color;
}

glm::vec3 Shader::GetVector3(string name) {
    this->Use();
    int location = this->GetLocation(name);

    glm::vec3 vector;
    glGetUniformfv(this->id, location, (float*)&vector);
    
    return vector;
}

glm::vec4 Shader::GetVector4(string name) {
    this->Use();
    int location = this->GetLocation(name);

    glm::vec4 vector;
    glGetUniformfv(this->id, location, (float*)&vector);
    
    return vector;
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
