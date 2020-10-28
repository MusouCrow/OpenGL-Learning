#ifndef RENDER_SHADER_H
#define RENDER_SHADER_H

#include "common.h"
#include "util/color.hpp"

class Shader {
public:
    Shader(string path);
    ~Shader();
    int GetId();
    int GetLocation(string name);
    void Use();

    void SetInt(string name, int value);
    void SetFloat(string name, float value);
    void SetColor(string name, Color& color);

    int GetInt(string name);
    float GetFloat(string name);
    Color GetColor(string name);
private:
    int id = 0;
    void Compile(int shader, string& src);
};

#endif