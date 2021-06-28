#include "resource.h"
#include "file.h"

auto Resource::textureMap = map<string, weak_ptr<Texture>>();
auto Resource::shaderMap = map<string, weak_ptr<Shader>>();
auto Resource::modelMap = map<string, weak_ptr<Model>>();
auto Resource::materialMap = map<string, weak_ptr<Material>>();

shared_ptr<Texture> Resource::LoadTexture(string path) {
    if (textureMap.find(path) != textureMap.end() && textureMap[path].use_count() > 0) {
        return textureMap[path].lock();
    }

    int width, height, channel;
    unsigned char* data = File::ReadImage(path, width, height, channel);
    auto texture = make_shared<Texture>(data, width, height, channel);
    File::FreeImage(data);
    textureMap[path] = texture;
    
    return texture;
}

shared_ptr<Shader> Resource::LoadShader(string path) {
    if (shaderMap.find(path) != shaderMap.end() && shaderMap[path].use_count() > 0) {
        return shaderMap[path].lock();
    }

    string vert_src = File::ReadFile(path + ".vs");
    string frag_src = File::ReadFile(path + ".fs");
    auto shader = make_shared<Shader>(vert_src, frag_src);
    shaderMap[path] = shader;

    return shader;
}

shared_ptr<Model> Resource::LoadModel(string path) {
    if (modelMap.find(path) != modelMap.end() && modelMap[path].use_count() > 0) {
        return modelMap[path].lock();
    }

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

    modelMap[path] = model;
    
    return model;
}

shared_ptr<Material> Resource::LoadMaterial(string path) {
    if (materialMap.find(path) != materialMap.end() && materialMap[path].use_count() > 0) {
        return materialMap[path].lock();
    }

    auto json = File::ReadJson(path);
    auto material = make_shared<Material>(json);
    materialMap[path] = material;
    
    return material;
}

void Resource::Log() {
    cout << "===== Texture =====" << endl;
    for (auto iter : textureMap) {
        cout << iter.first << ", " << iter.second.lock() << endl;
    }

    cout << "===== Shader =====" << endl;
    for (auto iter : shaderMap) {
        cout << iter.first << ", " << iter.second.lock() << endl;
    }

    cout << "===== Model =====" << endl;
    for (auto iter : modelMap) {
        cout << iter.first << ", " << iter.second.lock() << endl;
    }

    cout << "===== Material =====" << endl;
    for (auto iter : materialMap) {
        cout << iter.first << ", " << iter.second.lock() << endl;
    }
}