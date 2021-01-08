#include <glm/ext.hpp>
#include "Camera.h"

Camera::Camera(glm::mat4 projMat) : Object(), viewMatrix(1), projectionMatrix(projMat) {
    Camera::updateMatrix();
}

void Camera::lookAt(glm::vec3 target) {
    viewMatrix = glm::lookAt(position, target, glm::vec3(0, 1, 0));
    matrix = glm::inverse(viewMatrix);
    updateFromMatrix();
}

void Camera::updateMatrix() {
    Object::updateMatrix();
    viewMatrix = glm::inverse(matrix);
}

Camera Camera::perspective(float fov, float aspect, float near, float far) {
    return Camera(glm::perspective(fov, aspect, near, far));
}

Camera Camera::orthogonal(float left, float right, float bottom, float top, float near, float far) {
    return Camera(glm::ortho(left, right, bottom, top, near, far));
}
