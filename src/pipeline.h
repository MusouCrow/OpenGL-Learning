#ifndef PIPELINE_H
#define PIPELINE_H

#include <vector>
#include "common.h"
#include "render/camera.h"
#include "render/renderer/base.h"

class Pipeline {
public:
    static Pipeline* GetInstance();
    shared_ptr<Camera> camera;
    void Init(int width, int height);
    void Draw();
    void AddRenderer(shared_ptr<Renderer> renderer);
private:
    float r;
    float s;
    int dir;
    vector<shared_ptr<Renderer>> renderers;
    void OnCameraUpdated();
};

#endif