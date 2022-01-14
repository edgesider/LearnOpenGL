#version 330 core
in vec2 vTexCoord;
in vec3 vNormal;
in vec3 vPos;
out vec4 fragColor;

// 环境光强
uniform float ambientStrength;
// 镜面强度
uniform float specularStrength;
// 反光度
uniform float shininess;

uniform vec3 lightColor;
uniform vec3 lightPos;

uniform vec4 materialColor;

uniform vec3 viewPos;
uniform bool receiveLight;

uniform bool useTexture;
uniform sampler2D texture0;
uniform sampler2D texture1;

void main() {
    vec4 tex0Color = texture(texture0, vTexCoord);
    vec4 tex1Color = texture(texture1, vTexCoord);
    vec4 mixedTex = mix(tex0Color, tex1Color, .3);
    vec4 color;

    if (useTexture) {
        color = mix(texture(texture0, vTexCoord), texture(texture1, vTexCoord), .3);
    } else {
        color = materialColor;
    }

    if (receiveLight) {
        // 环境光
        vec3 ambient = ambientStrength * lightColor;

        // 漫反射
        vec3 normal = normalize(vNormal);
        vec3 lightDir = normalize(lightPos - vPos);
        vec3 diffuse = max(dot(normal, lightDir), 0) * lightColor;

        // 镜面反射
        vec3 viewDir = normalize(viewPos - vPos);
        float spec = pow(max(dot(viewDir, reflect(-lightDir, normal)), 0), max(shininess, 1));
        vec3 specular = specularStrength * spec * lightColor;

        fragColor = vec4(ambient + diffuse + specular, 0) * color;
    } else {
        fragColor = color;
    }
}
