#ifndef LEARN_GL_CUBE_H
#define LEARN_GL_CUBE_H

#include <glm/glm.hpp>
#include "Shader.h"
#include "Camera.h"
#include "Object.h"

class Cube : public Object {
private:
    static uint VAO_;
    static uint VBO;
    static uint EBO;

    const static float vertices[];
    const static uint indices[];

public:
    static void init();

    Cube();
};

#endif //LEARN_GL_CUBE_H
