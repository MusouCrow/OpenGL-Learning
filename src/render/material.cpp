#include <math.h>
#include <glm/vec3.hpp>

#include "util/color.hpp"
#include "lib/resource.h"
#include "lib/text.h"
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

            auto keyword = Text::ToKeyword(key);
            this->shader->SetKeyword(keyword, true);
        }
        else if (value.is_bool()) {
            this->shader->SetInt(key, (int)value.as_bool());
        }
        else if (value.is_float() || value.is_integer()) {
            this->shader->SetFloat(key, value.as_float());
        }
        else if (value.is_array()) {
            auto& array = value.as_array();

            if (array.size() == 4) {
                auto vec = glm::vec4(array[0].as_float(), array[1].as_float(), array[2].as_float(), array[3].as_float());
                this->shader->SetVector4(key, vec);
            }
        }
    }

    this->shader->Apply();
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