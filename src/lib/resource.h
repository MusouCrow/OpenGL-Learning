#ifndef LIB_RESOURCE_H
#define LIB_RESOURCE_H

#include <map>

#include "../common.h"
#include "render/texture.h"
#include "render/shader.h"
#include "render/mesh.h"
#include "render/material.h"
#include "util/prefab.h"

class Resource {
public:
    static shared_ptr<Texture> LoadTexture(string path);
    static shared_ptr<Shader> LoadShader(string path);
    static shared_ptr<Model> LoadModel(string path);
    static shared_ptr<Material> LoadMaterial(string path);
    static shared_ptr<Prefab> LoadPrefab(string path);
    static void Log();
    template <typename T>
    static void Log(map<string, weak_ptr<T>>& dataMap) {
        for (auto iter : dataMap) {
            cout << iter.first << ", " << iter.second.lock() << endl;
        }
    };
private:
    static map<string, weak_ptr<Texture>> textureMap;
    static map<string, weak_ptr<Shader>> shaderMap;
    static map<string, weak_ptr<Model>> modelMap;
    static map<string, weak_ptr<Material>> materialMap;
    static map<string, weak_ptr<Prefab>> prefabMap;
};

#endif