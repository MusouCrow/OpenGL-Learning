#include "lib/file.h"
#include "material.h"

Material::Material(string path) {
    jsonxx::json json = File::ReadJson(path);
    this->Init(json);
}

Material::Material(jsonxx::json& json) {
    this->Init(json);
}

void Material::Init(jsonxx::json& json) {
    this->shader = make_shared<Shader>("shader/" + json["Shader"].as_string());
    
    for (auto iter : json) {
        auto key = iter.key();
        auto value = iter.value();
        
        // 尾部命名为Map的是Texture
        if (key.substr(key.size() - 3, 3) == "Map") {
            auto texture = make_shared<Texture>("image/" + value.as_string());
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
    }
    
    this->shader->Use();
}