#version 330 core
out vec4 FragColor;

in vec2 uv;

uniform vec4 Color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
uniform sampler2D BaseMap;

void main() {
    FragColor = texture(BaseMap, uv) * Color;
}