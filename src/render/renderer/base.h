#ifndef RENDER_RENDERER_BASE_H
#define RENDER_RENDERER_BASE_H

#include <glm/glm.hpp>
#include "common.h"
#include "util/color.hpp"
#include "../shader.h"
#include "../texture.h"
#include "../mesh.h"
#include "../transform.h"

class Renderer {
public:
    Renderer(shared_ptr<Model> model, string shader, string image);
    void Draw();
    shared_ptr<Shader> shader;
    shared_ptr<Texture> texture;
    shared_ptr<Transform> transform;
private:
    shared_ptr<Model> model;
    void AdjustMatrix();
};

#endif