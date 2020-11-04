#ifndef RENDER_RENDERER_BASE_H
#define RENDER_RENDERER_BASE_H

#include <glm/glm.hpp>
#include "common.h"
#include "util/color.hpp"
#include "../shader.h"
#include "../texture.h"
#include "../mesh.hpp"

class Renderer {
public:
    Renderer(Mesh& mesh, string shader, string image, glm::mat4& model);
    void Draw();
    Shader* shader;
    Texture* texture;
private:
    Mesh mesh;

    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
    void InitVert();
};

#endif