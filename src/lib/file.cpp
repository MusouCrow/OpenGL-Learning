#include <fstream>
#include <sstream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "stb_image.h"
#include "file.h"
#include "../common.h"

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

shared_ptr<Model> File::ReadModel(string path) {
    path = File::FormatPath(path);
    
    Assimp::Importer importer;
    auto scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
        return nullptr;
    }

    auto model = make_shared<Model>();
    
    for (int n = 0; n < scene->mNumMeshes; n++) {
        vector<Vertex> vertices;
        vector<int> indices;
        auto meshData = scene->mMeshes[n];

        for (int i = 0; i < meshData->mNumVertices; i++) {
            auto& v = meshData->mVertices[i];
            auto& n = meshData->mNormals[i];
            auto& t = meshData->mTextureCoords[0][i];
            /*
            cout << "Vertices: " << v.x << ", " << v.y << ", " << v.z << endl;
            cout << "Normals: " << n.x << ", " << n.y << endl;
            cout << "TextureCoords: " << t.x << ", " << t.y << endl;
            */
            auto vertex = Vertex {
                glm::vec3(v.x, v.y, v.z),
                glm::vec3(n.x, n.y, n.z),
                glm::vec2(t.x, t.y)
            };

            vertices.push_back(vertex);
        }

        for (int i = 0; i < meshData->mNumFaces; i++) {
            auto& face = meshData->mFaces[i];
            
            for (int j = 0; j < face.mNumIndices; j++) {
                indices.push_back(face.mIndices[j]);
            }
        }
        
        auto mesh = make_shared<Mesh>(vertices, indices);
        model->meshes.push_back(mesh);
    }
    
    return model;
}