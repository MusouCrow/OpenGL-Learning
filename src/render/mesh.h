#ifndef RENDER_MESH_H
#define RENDER_MESH_H

#include "common.h"
#include "util/array.hpp"
#include "shader.h"

class Mesh {
public:
    Mesh(Array<float>& vertices, string shader);
    void Draw();
private:
    Array<float> vertices;
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
    Shader shader;
    void InitVert();
};

#endif