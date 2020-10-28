#ifndef RENDER_SHADER_H
#define RENDER_SHADER_H

#include "common.h"
#include "util/color.hpp"

class Shader {
public:
    Shader();
    Shader(string path);
    ~Shader();
    void Init(string path);
    int GetId();
    void SetColor(string name, Color& color);
private:
    int id = 0;
    void Compile(int shader, string& src);
};

#endif