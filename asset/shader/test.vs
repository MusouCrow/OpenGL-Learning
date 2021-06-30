#version 330 core

layout (location = 0) in vec3 v_vert;
layout (location = 1) in vec3 v_normal;
layout (location = 2) in vec2 v_texCoord;

out vec2 f_uv;
out vec3 f_normalWS;
out vec3 f_positionWS;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main() {
    f_uv = v_texCoord;
    f_normalWS = mat3(transpose(inverse(Model))) * v_normal;
    f_positionWS = vec3(Model * vec4(v_vert, 1.0));

    gl_Position = Projection * View * vec4(f_positionWS, 1.0);
}