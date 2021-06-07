#ifndef LIB_FILE_H
#define LIB_FILE_H

#include "../common.h"
#include "render/mesh.h"

class File {
public:
    static string FormatPath(string path);
    static string ReadFile(string path);
    static unsigned char* ReadImage(string path, int& width, int& height, int& channel);
    static void FreeImage(unsigned char* data);
    static shared_ptr<Mesh> ReadMesh(string path);
};

#endif