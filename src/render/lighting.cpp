#include "shader.h"
#include "lighting.h"

void Lighting::Apply() {
    Shader::SetGlobalVector3("_MainLightDir", this->mainLight.direction);
    Shader::SetGlobalColor("_MainLightColor", this->mainLight.color);
}