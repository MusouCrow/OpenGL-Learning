#ifndef RENDER_MESH_H
#define RENDER_MESH_H

#include <glm/glm.hpp>
#include "common.h"
#include "util/array.hpp"
#include "util/color.hpp"
#include "shader.h"
#include "texture.h"

class Mesh {
public:
    Mesh(Array<float>& vertices, Array<int>& indices, string shader, string image, glm::mat4& model);
    ~Mesh();
    void Draw();
    Shader* shader;
    Texture* texture;
private:
    Array<float> vertices;
    Array<int> indices;

    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
    void InitVert();
};

#endif