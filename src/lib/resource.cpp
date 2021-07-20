#include "resource.h"
#include "file.h"

auto Resource::textureMap = map<string, weak_ptr<Texture>>();
auto Resource::modelMap = map<string, weak_ptr<Model>>();
auto Resource::materialMap = map<string, weak_ptr<Material>>();
auto Resource::prefabMap = map<string, weak_ptr<Prefab>>();

#define CHECK_RES(dataMap, path) if (dataMap.find(path) != dataMap.end() && dataMap[path].use_count() > 0) return dataMap[path].lock();

shared_ptr<Texture> Resource::LoadTexture(string path) {
    CHECK_RES(textureMap, path);

    int width, height, channel;
    unsigned char* data = File::ReadImage("image/" + path, width, height, channel);
    auto texture = make_shared<Texture>(data, width, height, channel);
    File::FreeImage(data);
    textureMap[path] = texture;
    
    return texture;
}

shared_ptr<Shader> Resource::LoadShader(string path) {
    string vert_src = File::ReadFile("shader/" + path + ".vs");
    string frag_src = File::ReadFile("shader/" + path + ".fs");
    auto shader = make_shared<Shader>(vert_src, frag_src);

    return shader;
}

shared_ptr<Model> Resource::LoadModel(string path) {
    CHECK_RES(modelMap, path);

    auto importer = File::ReadModelImporter("model/" + path);

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
    CHECK_RES(materialMap, path);

    auto json = File::ReadJson("material/" + path + ".json");
    auto material = make_shared<Material>(json);
    materialMap[path] = material;
    
    return material;
}

shared_ptr<Prefab> Resource::LoadPrefab(string path) {
    CHECK_RES(prefabMap, path);

    auto json = File::ReadJson("prefab/" + path + ".json");
    auto prefab = make_shared<Prefab>(json);
    prefabMap[path] = prefab;
    
    return prefab;
}

void Resource::Log() {
    cout << "===== Texture =====" << endl;
    Log<Texture>(textureMap);

    cout << "===== Model =====" << endl;
    Log<Model>(modelMap);

    cout << "===== Material =====" << endl;
    Log<Material>(materialMap);
}

#undef CHECK_RES