#ifndef UTIL
#define UTIL

#include <iostream>

inline void printVec3(glm::vec3 v) {
    std::cout << v[0] << ", " << v[1] << ", " << v[2] << std::endl;
}

inline void printVec4(glm::vec4 v) {
    std::cout << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << std::endl;
}

inline void printMat4(glm::mat4 m) {
    std::cout << '[';
    printVec4(glm::row(m, 0));
    printVec4(glm::row(m, 1));
    printVec4(glm::row(m, 2));
    printVec4(glm::row(m, 3));
    std::cout << ']' << std::endl;
}

uint loadTexture(const std::string &path, bool alpha, bool flipVertical = false);

#endif