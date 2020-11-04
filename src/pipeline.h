#ifndef PIPELINE_H
#define PIPELINE_H

#include <vector>
#include "common.h"
#include "render/renderer/base.h"

class Pipeline {
public:
    static Pipeline* GetInstance();
    void Init(int width, int height);
    void Draw();
private:
    int shader;
    unsigned int vao;
    unsigned int vbo;
    vector<Renderer*> renderers;
};

#endif