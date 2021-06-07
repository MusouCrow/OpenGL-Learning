#version 330 core

layout (location = 0) in vec3 vert;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

out vec2 uv;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main() {
    uv = texCoord;
    gl_Position = Projection * View * Model * vec4(vert.x, vert.y, vert.z, 1.0);
}