#include "lib/resource.h"
#include "prefab.h"

#define GET_TRANSFORM(data, json) {auto arr = json.as_array();\
data = glm::vec3(arr[0].as_float(), arr[1].as_float(), arr[2].as_float());}

Prefab::Prefab(jsonxx::json& json) {
    GET_TRANSFORM(this->position, json["transform"]["position"]);
    GET_TRANSFORM(this->scale, json["transform"]["scale"]);
    GET_TRANSFORM(this->rotation, json["transform"]["rotation"]);

    this->model = Resource::LoadModel(json["model"].as_string());

    auto materials = json["materials"].as_array();

    for (auto m : materials) {
        auto material = Resource::LoadMaterial(m.as_string());
        this->materials.push_back(material);
    }
}

#undef GET_TRANSFORM