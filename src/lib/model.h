#ifndef LIB_MODEL_H
#define LIB_MODEL_H

#include "../common.h"
#include "render/mesh.h"

class Model {
public:
    static shared_ptr<Mesh> NewRectangle();
};

#endif