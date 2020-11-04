#ifndef RENDER_MESH_H
#define RENDER_MESH_H

#include "util/array.hpp"

struct Mesh {
    Array<float> vertices;
    Array<int> indices;
};

#endif