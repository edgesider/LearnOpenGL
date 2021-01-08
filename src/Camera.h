#ifndef LEARN_GL_CAMERA_H
#define LEARN_GL_CAMERA_H

#include <glm/glm.hpp>
#include "Object.h"

class Camera : public Object {
public:
    static Camera perspective(float fov, float aspect, float near, float far);

    static Camera orthogonal(float left, float right, float bottom, float top, float near, float far);

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    void lookAt(glm::vec3 target);

    void updateMatrix() override;

private:
    explicit Camera(glm::mat4 projMat);
};

#endif //LEARN_GL_CAMERA_H
