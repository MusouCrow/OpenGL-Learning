#ifndef RENDER_TEXTURE_H
#define RENDER_TEXTURE_H

#include "common.h"

class Texture {
public:
    Texture(unsigned char* data, int width, int height, int channel);
    ~Texture();
    void Bind(int index);
    void SetWrap(int wrap);
    void SetFilter(int filter);
    int GetWrap();
    int GetFilter();
    unsigned int GetId();
private:
    unsigned int id = 0;
    int wrap;
    int filter;
};

#endif