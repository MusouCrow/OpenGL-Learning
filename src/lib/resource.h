#ifndef LIB_RESOURCE_H
#define LIB_RESOURCE_H

#include "../common.h"
#include "render/texture.h"
#include "render/shader.h"
#include "render/mesh.h"
#include "render/material.h"

class Resource {
public:
    static shared_ptr<Texture> LoadTexture(string path);
    static shared_ptr<Shader> LoadShader(string path);
    static shared_ptr<Model> LoadModel(string path);
    static shared_ptr<Material> LoadMaterial(string path);
};

#endif