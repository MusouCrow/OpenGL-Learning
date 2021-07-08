#ifndef RENDER_SHADER_H
#define RENDER_SHADER_H

#include <glm/glm.hpp>
#include "common.h"
#include "util/color.hpp"

class Shader {
public:
    Shader(string path);
    Shader(string& vert_src, string& frag_src);
    ~Shader();
    int GetId();
    int GetLocation(string name);
    void Use();

    void SetInt(string name, int value);
    void SetFloat(string name, float value);
    void SetColor(string name, Color& color);
    void SetMatrix(string name, glm::mat4& matrix);
    void SetVector3(string name, glm::vec3& vector);
    void SetVector4(string name, glm::vec4& vector);
    int GetInt(string name);
    float GetFloat(string name);
    Color GetColor(string name);
    glm::vec3 GetVector3(string name);
    glm::vec4 GetVector4(string name);
private:
    int id = 0;
    void Compile(int shader, string& src);
};

#endif