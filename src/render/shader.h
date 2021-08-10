#ifndef RENDER_SHADER_H
#define RENDER_SHADER_H

#include <map>
#include <set>
#include <vector>
#include <glm/glm.hpp>
#include "common.h"
#include "util/color.hpp"

class Shader {
public:
    Shader(string vert_src, string frag_src);
    ~Shader();
    int GetId();
    int GetLocation(const string& name);
    void Use();
    void ApplyGlobal();

    void SetInt(const string& name, int value);
    void SetFloat(const string& name, float value);
    void SetColor(const string& name, const Color& value);
    void SetMatrix(const string& name, const glm::mat4& value);
    void SetVector3(const string& name, const glm::vec3& value);
    void SetVector4(const string& name, const glm::vec4& value);
    int GetInt(const string& name);
    float GetFloat(const string& name);
    Color GetColor(const string& name);
    glm::vec3 GetVector3(const string& name);
    glm::vec4 GetVector4(const string& name);

    void Apply();
    void SetKeyword(const string& key, bool value);
    bool HasKeyword(const string& key);
    
    static void SetGlobalInt(const string& name, int value);
    static void SetGlobalFloat(const string& name, float value);
    static void SetGlobalColor(const string& name, const Color& value);
    static void SetGlobalMatrix(const string& name, const glm::mat4& value);
    static void SetGlobalVector3(const string& name, const glm::vec3& value);
    static void SetGlobalVector4(const string& name, const glm::vec4& value);
    static int GetGlobalInt(const string& name);
    static float GetGlobalFloat(const string& name);
    static Color GetGlobalColor(const string& name);
    static glm::mat4 GetGlobalMatrix(const string& name);
    static glm::vec3 GetGlobalVector3(const string& name);
    static glm::vec4 GetGlobalVector4(const string& name);
private:
    int id = 0;
    set<string> keywords;
    string vert_src;
    string frag_src;

    void Init();
    void Compile(int shader, const string& src);
    string GenerateDefines();

    map<string, int> intMap;
    map<string, float> floatMap;
    map<string, Color> colorMap;
    map<string, glm::mat4> mat4Map;
    map<string, glm::vec3> vec3Map;
    map<string, glm::vec4> vec4Map;

    static map<string, int> IntMap;
    static map<string, float> FloatMap;
    static map<string, Color> ColorMap;
    static map<string, glm::mat4> Mat4Map;
    static map<string, glm::vec3> Vec3Map;
    static map<string, glm::vec4> Vec4Map;
};

#endif