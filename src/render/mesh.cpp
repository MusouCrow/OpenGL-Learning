#include "mesh.h"

Mesh::Mesh(Array<float>& vertices, Array<int>& indices) {
    this->vertices.Clone(vertices);
    this->indices.Clone(indices);
}

Mesh::~Mesh() {
    delete[] this->vertices.list;
    delete[] this->indices.list;
}
