#ifndef RENDER_RENDERER_BASE_H
#define RENDER_RENDERER_BASE_H

#include <glm/glm.hpp>
#include "common.h"
#include "util/color.hpp"
#include "../material.h"
#include "../shader.h"
#include "../texture.h"
#include "../mesh.h"
#include "../transform.h"

class Renderer {
public:
    Renderer(shared_ptr<Model> model, vector<shared_ptr<Material>> materials);
    void Draw();
    void SetMatrix(string name, glm::mat4& matrix);
    
    vector<shared_ptr<Material>> materials;
    shared_ptr<Transform> transform;
    shared_ptr<Model> model;
private:
    void AdjustMatrix();
};

#endif