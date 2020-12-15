#include "mesh.h"

Mesh::Mesh(Array<float>* vertices, Array<int>* indices) {
    if (vertices != nullptr) {
        this->vertices.Clone(*vertices);
    }

    if (indices != nullptr) {
        this->indices.Clone(*indices);
    }
}

Mesh::~Mesh() {
    delete[] this->vertices.list;
    delete[] this->indices.list;
}
