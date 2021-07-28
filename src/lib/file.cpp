#include <fstream>
#include <sstream>

#include "stb_image.h"
#include "file.h"

string File::FormatPath(string path) {
    return "../asset/" + path;
}

string File::ReadFile(string path) {
    path = File::FormatPath(path);
    ifstream file(path);

    if (!file.is_open()) {
        cout << "Can't open file: " << path << endl;
        return "";
    }

    stringstream stream;
    stream << file.rdbuf();
    file.close();

    return stream.str();
}

unsigned char* File::ReadImage(string path, int& width, int& height, int& channel) {
    path = File::FormatPath(path);
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &channel, 0);
    
    if (data == nullptr) {
        cout << "Can't open image: " << path << endl;
    }
    
    return data;
}

void File::FreeImage(unsigned char* data) {
    stbi_image_free(data);
}

shared_ptr<Assimp::Importer> File::ReadModelImporter(string path) {
    path = File::FormatPath(path);

    auto importer = make_shared<Assimp::Importer>();
    auto scene = importer->ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        cout << "ERROR::ASSIMP::" << importer->GetErrorString() << endl;
        return nullptr;
    }
    
    return importer;
}

jsonxx::json File::ReadJson(string path) {
    path = File::FormatPath(path);
    string content = File::ReadFile(path);
    
    auto json = jsonxx::json::parse(content);

    return json;
}