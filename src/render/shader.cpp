#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include "lib/file.h"
#include "shader.h"

auto Shader::IntMap = map<string, int>();
auto Shader::FloatMap = map<string, float>();
auto Shader::ColorMap = map<string, Color>();
auto Shader::Mat4Map = map<string, glm::mat4>();
auto Shader::Vec3Map = map<string, glm::vec3>();
auto Shader::Vec4Map = map<string, glm::vec4>();

#define READY(name) this->Use(); int location = this->GetLocation(name);
#define GEN_GLOBAL_GET_FUNC(T, F, map) void Shader::SetGlobal##F(const string& name, T value) { map[name] = value; }
#define GEN_GLOBAL_SET_FUNC(T, F, map) T Shader::GetGlobal##F(const string& name) { return map[name]; }
#define APPLY_SHADER(map, func) for (auto iter : map) { func(iter.first, iter.second); }

GEN_GLOBAL_GET_FUNC(int, Int, Shader::IntMap)
GEN_GLOBAL_GET_FUNC(float, Float, Shader::FloatMap)
GEN_GLOBAL_GET_FUNC(const Color&, Color, Shader::ColorMap)
GEN_GLOBAL_GET_FUNC(const glm::mat4&, Matrix, Shader::Mat4Map)
GEN_GLOBAL_GET_FUNC(const glm::vec3&, Vector3, Shader::Vec3Map)
GEN_GLOBAL_GET_FUNC(const glm::vec4&, Vector4, Shader::Vec4Map)

GEN_GLOBAL_SET_FUNC(int, Int, Shader::IntMap)
GEN_GLOBAL_SET_FUNC(float, Float, Shader::FloatMap)
GEN_GLOBAL_SET_FUNC(Color, Color, Shader::ColorMap)
GEN_GLOBAL_SET_FUNC(glm::mat4, Matrix, Shader::Mat4Map)
GEN_GLOBAL_SET_FUNC(glm::vec3, Vector3, Shader::Vec3Map)
GEN_GLOBAL_SET_FUNC(glm::vec4, Vector4, Shader::Vec4Map)

Shader::Shader(string vert_src, string frag_src) {
    this->vert_src = vert_src;
    this->frag_src = frag_src;
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

void Shader::Apply() {
    this->Init();
    
    APPLY_SHADER(this->intMap, SetInt)
    APPLY_SHADER(this->floatMap, SetFloat)
    APPLY_SHADER(this->colorMap, SetColor)
    APPLY_SHADER(this->mat4Map, SetMatrix)
    APPLY_SHADER(this->vec3Map, SetVector3)
    APPLY_SHADER(this->vec4Map, SetVector4)
}

void Shader::ApplyGlobal() {
    APPLY_SHADER(Shader::IntMap, SetInt)
    APPLY_SHADER(Shader::FloatMap, SetFloat)
    APPLY_SHADER(Shader::ColorMap, SetColor)
    APPLY_SHADER(Shader::Mat4Map, SetMatrix)
    APPLY_SHADER(Shader::Vec3Map, SetVector3)
    APPLY_SHADER(Shader::Vec4Map, SetVector4)
}

void Shader::SetInt(const string& name, int value) {
    this->intMap[name] = value;
    
    if (this->id > 0) {
        READY(name);
        glUniform1i(location, value);
    }
}

void Shader::SetFloat(const string& name, float value) {
    this->floatMap[name] = value;
    
    if (this->id > 0) {
        READY(name);
        glUniform1f(location, value);
    }
}

void Shader::SetColor(const string& name, const Color& value) {
    this->colorMap[name] = value;
    
    if (this->id > 0) {
        READY(name);
        glUniform4f(location, value.r, value.g, value.b, value.a);
    }
}

void Shader::SetMatrix(const string& name, const glm::mat4& value) {
    this->mat4Map[name] = value;
    
    if (this->id > 0) {
        READY(name);
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }
}

void Shader::SetVector3(const string& name, const glm::vec3& value) {
    this->vec3Map[name] = value;
    
    if (this->id > 0) {
        READY(name);
        glUniform3f(location, value.x, value.y, value.z);
    }
}

void Shader::SetVector4(const string& name, const glm::vec4& value) {
    this->vec4Map[name] = value;
    
    if (this->id > 0) {
        READY(name);
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }
}

int Shader::GetInt(const string& name) {
    return this->intMap[name];
}

float Shader::GetFloat(const string& name) {
    return this->floatMap[name];
}

Color Shader::GetColor(const string& name) {
    return this->colorMap[name];
}

glm::vec3 Shader::GetVector3(const string& name) {
    return this->Vec3Map[name];
}

glm::vec4 Shader::GetVector4(const string& name) {
    return this->vec4Map[name];
}

void Shader::SetKeyword(const string& key, bool value) {
    if (this->HasKeyword(key) == value) {
        return;
    }

    if (value) {
        this->keywords.insert(key);
    }
    else {
        this->keywords.erase(key);
    }
}

bool Shader::HasKeyword(const string& key) {
    return this->keywords.find(key) != this->keywords.end();
}

void Shader::Init() {
    if (this->id > 0) {
        glDeleteProgram(this->id);
    }

    int vert_shader = glCreateShader(GL_VERTEX_SHADER);
    int frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    string head = this->GenerateDefines();
    
    this->Compile(vert_shader, head + this->vert_src);
    this->Compile(frag_shader, head + this->frag_src);
    
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

string Shader::GenerateDefines() {
    string code = "#version 330 core\n";

    for (auto key : this->keywords) {
        code += "#define " + key + "\n";
    }

    return code;
}

#undef READY
#undef GEN_GLOBAL_GET_FUNC
#undef GEN_GLOBAL_SET_FUNC
#undef APPLY_GLOBAL_SHADER