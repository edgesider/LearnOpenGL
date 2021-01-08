#include <glad/glad.h>
#include <stdexcept>
#include "Cube.h"
#include "Shader.h"

uint Cube::VAO_ = -1;
uint Cube::VBO = -1;
uint Cube::EBO = -1;

const float Cube::vertices[] = {
//      ---- 位置 ----     - 纹理坐标 -
        // 前
        0.5f, 0.5f, 0.5f, 2.0f, 2.0f, 0, 0, 1,
        0.5f, -0.5f, 0.5f, 2.0f, 0.0f, 0, 0, 1,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0, 0, 1,
        -0.5f, 0.5f, 0.5f, 0.0f, 2.0f, 0, 0, 1,

        // 后
        0.5f, 0.5f, -0.5f, 2.0f, 2.0f, 0, 0, -1,
        0.5f, -0.5f, -0.5f, 2.0f, 0.0f, 0, 0, -1,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0, 0, -1,
        -0.5f, 0.5f, -0.5f, 0.0f, 2.0f, 0, 0, -1,

        // 左
        -0.5f, 0.5f, 0.5f, 2.0f, 2.0f, -1, 0, 0,
        -0.5f, 0.5f, -0.5f, 2.0f, 0.0f, -1, 0, 0,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1, 0, 0,
        -0.5f, -0.5f, 0.5f, 0.0f, 2.0f, -1, 0, 0,

        // 右
        0.5f, 0.5f, 0.5f, 2.0f, 2.0f, 1, 0, 0,
        0.5f, 0.5f, -0.5f, 2.0f, 0.0f, 1, 0, 0,
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1, 0, 0,
        0.5f, -0.5f, 0.5f, 0.0f, 2.0f, 1, 0, 0,

        // 上
        0.5f, 0.5f, 0.5f, 2.0f, 2.0f, 0, 1, 0,
        0.5f, 0.5f, -0.5f, 2.0f, 0.0f, 0, 1, 0,
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0, 1, 0,
        -0.5f, 0.5f, 0.5f, 0.0f, 2.0f, 0, 1, 0,

        // 下
        0.5f, -0.5f, 0.5f, 2.0f, 2.0f, 0, -1, 0,
        0.5f, -0.5f, -0.5f, 2.0f, 0.0f, 0, -1, 0,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0, -1, 0,
        -0.5f, -0.5f, 0.5f, 0.0f, 2.0f, 0, -1, 0,
};
const uint Cube::indices[] = {
        0, 1, 3,
        1, 2, 3,
        4, 5, 7,
        5, 6, 7,
        8, 9, 11,
        9, 10, 11,
        12, 13, 15,
        13, 14, 15,
        16, 17, 19,
        17, 18, 19,
        20, 21, 23,
        21, 22, 23,
};

void Cube::init() {
    if (VAO_ != -1)
        throw std::runtime_error("Cube has been initialized");
    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO_);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (5 * sizeof(float)));
    glEnableVertexAttribArray(2);
}


Cube::Cube() : Object() {
    if (VAO_ == -1)
        init();
    VAO = VAO_;
    this->vertexCount = sizeof(indices) / sizeof(float);
    updateMatrix();
}
