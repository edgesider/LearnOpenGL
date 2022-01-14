#include <fstream>
#include <iostream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Shader.h"

using namespace std;

Shader::Shader(const GLchar *vertexPath, const GLchar *fragmentPath) {
    int success;
    char info[512];
    uint vertex = compileFile(vertexPath, GL_VERTEX_SHADER),
            fragment = compileFile(fragmentPath, GL_FRAGMENT_SHADER);

    id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id, sizeof(info), nullptr, info);
        throw runtime_error(string("shaders link failed: ") + info);
    }
}

void Shader::use() const {
    glUseProgram(id);
}

void Shader::setUniform(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int) value);
}

void Shader::setUniform(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setUniform(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setUniform(const std::string &name, float v1, float v2, float v3, float v4) const {
    glUniform4f(glGetUniformLocation(id, name.c_str()), v1, v2, v3, v4);
}

void Shader::setUniform(const std::string &name, glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setUniform(const std::string &name, float v1, float v2, float v3) const {
    glUniform3f(glGetUniformLocation(id, name.c_str()), v1, v2, v3);
}

void Shader::setUniform(const std::string &name, glm::vec3 v) const {
    glUniform3f(glGetUniformLocation(id, name.c_str()), v.x, v.y, v.z);
}

uint Shader::compileFile(const string &path, uint type) {
    string code;
    ifstream file;
    file.exceptions(ifstream::failbit | ifstream::badbit);
    try {
        file.open(path);
        stringstream stream;
        stream << file.rdbuf();
        file.close();
        code = stream.str();
    } catch (ifstream::failure &e) {
        cout << "read file failed: " << e.what() << endl;
        throw e;
    }

    uint shader;
    int success;
    char info[512];
    const char *c_str;
    shader = glCreateShader(type);
    c_str = code.c_str();
    glShaderSource(shader, 1, &c_str, nullptr);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, sizeof(info), nullptr, info);
        throw runtime_error(string("shader compile failed: ") + info);
    }
    return shader;
}
