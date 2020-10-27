#ifndef RENDER_SHADER_H
#define RENDER_SHADER_H

#include "common.h"

class Shader {
public:
    Shader();
    Shader(string path);
    void Init(string path);
    int GetId();
private:
    int id;
    void Compile(int shader, string& src);
};

#endif