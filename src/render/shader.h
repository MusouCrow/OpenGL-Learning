#ifndef RENDER_SHADER_H
#define RENDER_SHADER_H

#include <map>
#include <glm/glm.hpp>
#include "common.h"
#include "util/color.hpp"

class Shader {
public:
    Shader(const string& path);
    Shader(const string& vert_src, const string& frag_src);
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
    void Compile(int shader, const string& src);

    static map<string, int> intMap;
    static map<string, float> floatMap;
    static map<string, Color> colorMap;
    static map<string, glm::mat4> mat4Map;
    static map<string, glm::vec3> vec3Map;
    static map<string, glm::vec4> vec4Map;
};

#endif