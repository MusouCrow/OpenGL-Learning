#ifndef RENDER_MESH_H
#define RENDER_MESH_H

#include <vector>
#include "../common.h"

class Mesh {
public:
    Mesh(vector<float> vertices, vector<int> indices);
    vector<float> vertices;
    vector<int> indices;
};

#endif