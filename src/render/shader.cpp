#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include "lib/file.h"
#include "shader.h"

auto Shader::intMap = map<string, int>();
auto Shader::floatMap = map<string, float>();
auto Shader::colorMap = map<string, Color>();
auto Shader::mat4Map = map<string, glm::mat4>();
auto Shader::vec3Map = map<string, glm::vec3>();
auto Shader::vec4Map = map<string, glm::vec4>();

#define READY(name) this->Use(); int location = this->GetLocation(name);
#define GEN_GLOBAL_GET_FUNC(T, F, map) void Shader::SetGlobal##F(const string& name, T value) { map[name] = value; }
#define GEN_GLOBAL_SET_FUNC(T, F, map) T Shader::GetGlobal##F(const string& name) { return map[name]; }
#define APPLY_GLOBAL_SHADER(map, func) for (auto iter : map) { func(iter.first, iter.second); }

GEN_GLOBAL_GET_FUNC(int, Int, Shader::intMap)
GEN_GLOBAL_GET_FUNC(float, Float, Shader::floatMap)
GEN_GLOBAL_GET_FUNC(const Color&, Color, Shader::colorMap)
GEN_GLOBAL_GET_FUNC(const glm::mat4&, Matrix, Shader::mat4Map)
GEN_GLOBAL_GET_FUNC(const glm::vec3&, Vector3, Shader::vec3Map)
GEN_GLOBAL_GET_FUNC(const glm::vec4&, Vector4, Shader::vec4Map)

GEN_GLOBAL_SET_FUNC(int, Int, Shader::intMap)
GEN_GLOBAL_SET_FUNC(float, Float, Shader::floatMap)
GEN_GLOBAL_SET_FUNC(Color, Color, Shader::colorMap)
GEN_GLOBAL_SET_FUNC(glm::mat4, Matrix, Shader::mat4Map)
GEN_GLOBAL_SET_FUNC(glm::vec3, Vector3, Shader::vec3Map)
GEN_GLOBAL_SET_FUNC(glm::vec4, Vector4, Shader::vec4Map)

Shader::Shader(const string& vert_src, const string& frag_src) {
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

int Shader::GetLocation(const string& name) {
    return glGetUniformLocation(this->id, name.c_str());
}

void Shader::Use() {
    glUseProgram(this->id);
}

void Shader::ApplyGlobal() {
    APPLY_GLOBAL_SHADER(Shader::intMap, SetInt)
    APPLY_GLOBAL_SHADER(Shader::floatMap, SetFloat)
    APPLY_GLOBAL_SHADER(Shader::colorMap, SetColor)
    APPLY_GLOBAL_SHADER(Shader::mat4Map, SetMatrix)
    APPLY_GLOBAL_SHADER(Shader::vec3Map, SetVector3)
    APPLY_GLOBAL_SHADER(Shader::vec4Map, SetVector4)
}

void Shader::SetInt(const string& name, int value) {
    READY(name);
    glUniform1i(location, value);
}

void Shader::SetFloat(const string& name, float value) {
    READY(name);
    glUniform1f(location, value);
}

void Shader::SetColor(const string& name, const Color& value) {
    READY(name);
    glUniform4f(location, value.r, value.g, value.b, value.a);
}

void Shader::SetMatrix(const string& name, const glm::mat4& value) {
    READY(name);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetVector3(const string& name, const glm::vec3& value) {
    READY(name);
    glUniform3f(location, value.x, value.y, value.z);
}

void Shader::SetVector4(const string& name, const glm::vec4& value) {
    READY(name);
    glUniform4f(location, value.x, value.y, value.z, value.w);
}

int Shader::GetInt(const string& name) {
    READY(name);
    
    int value;
    glGetUniformiv(this->id, location, &value);
    
    return value;
}

float Shader::GetFloat(const string& name) {
    READY(name);

    float value;
    glGetUniformfv(this->id, location, &value);
    
    return value;
}

Color Shader::GetColor(const string& name) {
    READY(name);

    Color color;
    glGetUniformfv(this->id, location, (float*)&color);
    
    return color;
}

glm::vec3 Shader::GetVector3(const string& name) {
    READY(name);

    glm::vec3 vector;
    glGetUniformfv(this->id, location, (float*)&vector);
    
    return vector;
}

glm::vec4 Shader::GetVector4(const string& name) {
    READY(name);

    glm::vec4 vector;
    glGetUniformfv(this->id, location, (float*)&vector);
    
    return vector;
}

void Shader::Compile(int shader, const string& src) {
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

#undef READY
#undef GEN_GLOBAL_GET_FUNC
#undef GEN_GLOBAL_SET_FUNC
#undef APPLY_GLOBAL_SHADER