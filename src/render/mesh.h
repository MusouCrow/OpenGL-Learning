#ifndef RENDER_MESH_H
#define RENDER_MESH_H

#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "../common.h"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

class Mesh {
public:
    Mesh(vector<Vertex> vertices, vector<int> indices);
    ~Mesh();
    void Draw();
private:
    void Setup();
    void Unload();
    vector<Vertex> vertices;
    vector<int> indices;
    bool hasSetup = false;
    unsigned int vao = 0;
    unsigned int vbo = 0;
    unsigned int ebo = 0;
};

struct Model {
    vector<shared_ptr<Mesh>> meshes;
};

#endif