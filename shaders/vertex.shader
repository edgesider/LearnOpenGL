#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;
out vec2 vTexCoord;
out vec3 vNormal;
out vec3 vPos;

uniform mat4 model, view, projection;

void main() {
    gl_Position = projection * view * model * vec4(pos, 1);
    vTexCoord = texCoord;
    vNormal = mat3(transpose(inverse(model))) * vec3(normal);
    vPos = vec3(model * vec4(pos, 1));
}
