#ifndef LIB_FILE_H
#define LIB_FILE_H

#include <jsonxx/json.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../common.h"
#include "render/mesh.h"

class File {
public:
    static string FormatPath(string path);
    static string ReadFile(string path);
    static unsigned char* ReadImage(string path, int& width, int& height, int& channel);
    static void FreeImage(unsigned char* data);
    static shared_ptr<Assimp::Importer> ReadModelImporter(string path);
    static jsonxx::json ReadJson(string path);
};

#endif