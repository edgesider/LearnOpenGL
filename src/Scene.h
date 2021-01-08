#ifndef LEARN_GL_SCENE_H
#define LEARN_GL_SCENE_H

#include <vector>
#include "Object.h"
#include "Camera.h"

class Scene {
public:
    Scene();

    std::vector<Object *> objects;
    glm::vec4 color;
    glm::vec3 lightColor;
    glm::vec3 lightPosition;

    void render(Shader &shader, Camera &camera);

    void add(Object *object);
};


#endif //LEARN_GL_SCENE_H
