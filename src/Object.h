#ifndef LEARN_GL_OBJECT_H
#define LEARN_GL_OBJECT_H

#include <glm/glm.hpp>
#include "Shader.h"

class Object {
public:
    Object();

    glm::vec3 position;
    glm::vec3 rotation;
    glm::mat4 matrix;

    uint VAO, vertexCount;
    glm::vec4 materialColor;
    uint texture0, texture1;

    bool receiveLight;
    // 环境光强，反光度，镜面强度
    float ambientStrength, shininess, specularStrength;

    virtual void updateMatrix();

    void updateFromMatrix();
};

#endif //LEARN_GL_OBJECT_H
