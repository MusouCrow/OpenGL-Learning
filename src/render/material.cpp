#include <math.h>
#include <glm/vec3.hpp>

#include "util/color.hpp"
#include "lib/resource.h"
#include "material.h"

Material::Material(jsonxx::json& json) {
    this->shader = Resource::LoadShader(json["Shader"].as_string());

    for (auto iter : json) {
        auto key = iter.key();
        auto value = iter.value();
        
        // 尾部命名为Map的是Texture
        if (key.substr(key.size() - 3, 3) == "Map") {
            auto texture = Resource::LoadTexture(value.as_string());
            this->textureMap[key] = texture;
        }
        else if (value.is_bool()) {
            this->shader->SetInt(key, (int)value.as_bool());
        }
        else if (value.is_float()) {
            this->shader->SetFloat(key, value.as_float());
        }
    }
}
shared_ptr<Shader> Material::GetShader() {
    return this->shader;
}

shared_ptr<Texture> Material::GetTexture(string name) {
    if (this->textureMap.find(name) == this->textureMap.end()) {
        return nullptr;
    }

    return this->textureMap[name];
}

void Material::Bind() {
    int i = -1;
    for (auto iter : this->textureMap) {
        i++;
        iter.second->Bind(i);
        this->shader->SetInt(iter.first, i);
    }
    
    this->shader->ApplyGlobal();
    this->shader->Use();
}