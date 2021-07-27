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
uniform sampler2D SpecMap;
uniform sampler2D NormalMap;

float Diffuse(vec3 normal, vec3 lightDir) {
    return max(dot(normal, lightDir), 0);
}

float Specular(vec3 normal, vec3 lightDir, vec3 viewDir) {
    vec3 halfVec = normalize(lightDir + viewDir);
    float rate = dot(normal, halfVec);

    return pow(max(rate, 0), 8);
}

void main() {
    // vec3 normal = texture(NormalMap, f_uv).rgb;
    // normal = normalize(normal * 2.0 - 1.0);
    
    vec3 normal = normalize(f_normalWS);
    vec3 viewDir = _ViewPos - f_positionWS;

    vec3 diffuse = Diffuse(normal, _LightDir) * texture(BaseMap, f_uv).rgb;
    vec3 specular = Specular(normal, _LightDir, viewDir) * texture(SpecMap, f_uv).rgb;

    vec3 litColor = 0.1 + (diffuse + specular) * _LightColor.rgb;
    vec4 color = Color * vec4(litColor, 1.0);

    FragColor = color;
}