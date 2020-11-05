#ifndef RENDER_RENDERER_BASE_H
#define RENDER_RENDERER_BASE_H

#include <glm/glm.hpp>
#include "common.h"
#include "util/color.hpp"
#include "../shader.h"
#include "../texture.h"
#include "../mesh.h"

class Renderer {
public:
    Renderer(shared_ptr<Mesh> mesh, string shader, string image, glm::mat4& model);
    void Draw();
    shared_ptr<Shader> shader;
    shared_ptr<Texture> texture;
private:
    shared_ptr<Mesh> mesh;
    
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
    void InitVert();
};

#endif