#ifndef LEARN_GL_SHADER_H
#define LEARN_GL_SHADER_H

#include <glad/glad.h>
#include <sys/types.h>
#include <string>
#include <utility>

class Shader {
private:
    static uint compileFile(const std::string &path, uint type);

public:
    uint id;

    Shader(const GLchar *vertexPath, const GLchar *fragmentPath);

    void use() const;

    void setUniform(const std::string &name, bool value) const;

    void setUniform(const std::string &name, int value) const;

    void setUniform(const std::string &name, float value) const;

    void setUniform(const std::string &name, float v1, float v2, float v3, float v4) const;

    void setUniform(const std::string &name, glm::mat4 &mat) const;

    void setUniform(const std::string &name, glm::vec3 v) const;

    void setUniform(const std::string &name, float v1, float v2, float v3) const;
};


#endif //LEARN_GL_SHADER_H
