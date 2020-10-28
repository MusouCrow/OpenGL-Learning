#ifndef RENDER_MESH_H
#define RENDER_MESH_H

#include "common.h"
#include "util/array.hpp"
#include "util/color.hpp"
#include "shader.h"

class Mesh {
public:
    Mesh(Array<float>& vertices, Array<int>& indices, string shader, Color& color);
    ~Mesh();
    void Draw();
    Shader shader;
private:
    Array<float> vertices;
    Array<int> indices;

    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
    void InitVert();
};

#endif