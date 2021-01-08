#include <glm/gtx/euler_angles.hpp>
#include "Object.h"

Object::Object() : position(), rotation(), matrix(1),
                   vertexCount(0), VAO(-1), materialColor(0, 0, 0, 1),
                   texture0(-1), texture1(-1),
                   receiveLight(true), ambientStrength(.3), shininess(64), specularStrength(.4) {
}

void Object::updateMatrix() {
    auto m = glm::eulerAngleYXZ(rotation.y, rotation.x, rotation.z);
    m[3] = glm::vec4(position, 1);
    matrix = m;
}

void Object::updateFromMatrix() {
    position = matrix[3];
    glm::extractEulerAngleYXZ(matrix, rotation.y, rotation.x, rotation.z);
}
