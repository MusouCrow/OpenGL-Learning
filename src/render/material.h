#ifndef RENDER_MATERIAL_H
#define RENDER_MATERIAL_H

#include <map>
#include <jsonxx/json.hpp>

#include "../common.h"
#include "shader.h"
#include "texture.h"

class Material {
public:
    Material(string path);
    Material(jsonxx::json& json);
    shared_ptr<Shader> GetShader();
    shared_ptr<Texture> GetTexture(string name);
    void Bind();
private:
    void Init(jsonxx::json& json);
    shared_ptr<Shader> shader;
    map<string, shared_ptr<Texture>> textureMap;
};

#endif