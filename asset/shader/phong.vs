#version 330 core

layout (location = 0) in vec3 v_vert;
layout (location = 1) in vec3 v_normal;
layout (location = 2) in vec3 v_tangent;
layout (location = 3) in vec3 v_bitangent;
layout (location = 4) in vec2 v_texCoord;

out vec2 f_uv;
out vec3 f_normalWS;
out vec3 f_tangentWS;
out vec3 f_bitangentWS;
out vec3 f_positionWS;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main() {
    mat3 normalMat = mat3(transpose(inverse(Model)));
    
    f_uv = v_texCoord;
    f_normalWS = normalize(normalMat * v_normal);
    f_tangentWS = normalize(normalMat * v_tangent);
    f_bitangentWS = normalize(normalMat * v_bitangent);
    f_positionWS = vec3(Model * vec4(v_vert, 1.0));

    gl_Position = Projection * View * vec4(f_positionWS, 1.0);
}