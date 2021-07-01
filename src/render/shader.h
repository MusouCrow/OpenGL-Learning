#ifndef RENDER_SHADER_H
#define RENDER_SHADER_H

#include <type_traits>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "common.h"
#include "util/color.hpp"

class Shader {
public:
    Shader(string path);
    Shader(string& vert_src, string& frag_src);
    ~Shader();
    int GetId();
    int GetLocation(string name);
    void Use();

    template <typename T>
    void SetValue(string name, const T& value) {
        this->Use();
        int location = this->GetLocation(name);
        
        if constexpr(is_same<T, int>::value) {
            glUniform1i(location, value);
        }
        else if constexpr(is_same<T, float>::value) {
            glUniform1f(location, value);
        }
        else if constexpr(is_same<T, Color>::value) {
            glUniform4f(location, value.r, value.g, value.b, value.a);
        }
        else if constexpr(is_same<T, glm::mat4>::value) {
            glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
        }
        else if constexpr(is_same<T, glm::vec3>::value) {
            glUniform3f(location, value.x, value.y, value.z);
        }
        else if constexpr(is_same<T, glm::vec4>::value) {
            glUniform4f(location, value.x, value.y, value.z, value.w);
        }
    };
    template <typename T>
    T GetValue(string name) {
        this->Use();
        int location = this->GetLocation(name);

        T value;

        if constexpr(is_same<T, int>::value) {
            glGetUniformiv(this->id, location, &value);
        }
        else if constexpr(is_same<T, float>::value) {
            glGetUniformfv(this->id, location, &value);
        }
        else if constexpr(is_same<T, Color>::value || is_same<T, glm::vec3>::value || is_same<T, glm::vec4>::value) {
            glGetUniformfv(this->id, location, (float*)&value);
        }
        
        return value;
    };
private:
    int id = 0;
    void Compile(int shader, string& src);
};

#endif