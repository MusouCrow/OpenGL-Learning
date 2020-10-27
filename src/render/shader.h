#ifndef RENDER_SHADER_H
#define RENDER_SHADER_H

#include "common.h"

class Shader {
public:
    Shader();
    Shader(string path);
    ~Shader();
    void Init(string path);
    int GetId();
private:
    int id = 0;
    void Compile(int shader, string& src);
};

#endif