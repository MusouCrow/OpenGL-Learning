#ifndef RENDER_MESH_H
#define RENDER_MESH_H

#include "util/array.hpp"

class Mesh {
public:
    Mesh(Array<float>* vertices, Array<int>* indices);
    ~Mesh();
    Array<float> vertices;
    Array<int> indices;
};

#endif