#version 330 core
out vec4 FragColor;

in vec2 f_uv;
in vec3 f_normalWS;
in vec3 f_positionWS;

uniform vec3 _LightDir;
uniform vec4 _LightColor;
uniform vec3 _ViewPos;

uniform vec4 Color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
uniform sampler2D BaseMap;

float Diffuse(vec3 normal, vec3 lightDir) {
    return max(dot(normal, lightDir), 0);
}

float Specular(vec3 normal, vec3 lightDir, vec3 viewDir) {
    vec3 halfVec = normalize(lightDir + viewDir);
    float rate = dot(normal, halfVec);

    return pow(max(rate, 0), 8);
}

void main() {
    vec3 normal = normalize(f_normalWS);
    vec3 viewDir = _ViewPos - f_positionWS;

    float diffuse = Diffuse(normal, _LightDir);
    float specular = Specular(normal, _LightDir, viewDir);

    vec3 litColor = 0.2 + (diffuse + specular) * _LightColor.rgb;
    vec4 color = texture(BaseMap, f_uv) * Color;
    color.rgb *= litColor;

    FragColor = color;
}