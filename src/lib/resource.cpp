#include "resource.h"
#include "file.h"

shared_ptr<Texture> Resource::LoadTexture(string path) {
    int width, height, channel;
    unsigned char* data = File::ReadImage(path, width, height, channel);
    auto texture = make_shared<Texture>(data, width, height, channel);
    File::FreeImage(data);

    return texture;
}

shared_ptr<Shader> Resource::LoadShader(string path) {
    string vert_src = File::ReadFile(path + ".vs");
    string frag_src = File::ReadFile(path + ".fs");
    auto shader = make_shared<Shader>(vert_src, frag_src);

    return shader;
}

shared_ptr<Model> Resource::LoadModel(string path) {
    auto importer = File::ReadModelImporter(path);

    if (importer == nullptr) {
        return nullptr;
    }

    auto scene = importer->GetScene();
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

shared_ptr<Material> Resource::LoadMaterial(string path) {
    auto json = File::ReadJson(path);
    auto material = make_shared<Material>(json);
    
    return material;
}