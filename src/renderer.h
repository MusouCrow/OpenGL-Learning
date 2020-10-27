#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "common.h"
#include "render/mesh.h"

class Renderer {
public:
    static Renderer* GetInstance();
    void Init(int width, int height);
    void Draw();
private:
    int shader;
    unsigned int vao;
    unsigned int vbo;
    vector<Mesh*> meshs;
};

#endif