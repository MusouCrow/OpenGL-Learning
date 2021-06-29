#ifndef UTIL_PREFAB_H
#define UTIL_PREFAB_H

#include <vector>
#include <glm/glm.hpp>
#include <jsonxx/json.hpp>

#include "common.h"
#include "render/mesh.h"
#include "render/material.h"

struct Prefab {
    Prefab(jsonxx::json& json);
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotation;
    shared_ptr<Model> model;
    vector<shared_ptr<Material>> materials;
};

#endif