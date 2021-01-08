#include "Scene.h"

Scene::Scene() : color(0, 0, 0, 0),
                 lightColor(1, 1, 1), lightPosition() {
}

void Scene::render(Shader &shader, Camera &camera) {
    shader.use();
    shader.setUniform("view", camera.viewMatrix);
    shader.setUniform("projection", camera.projectionMatrix);
    shader.setUniform("viewPos", camera.position);
    shader.setUniform("lightColor", lightColor);
    shader.setUniform("lightPos", lightPosition);
    for (auto obj: objects) {
        if (obj->VAO == -1 || obj->vertexCount <= 0)
            continue;
        glBindVertexArray(obj->VAO);
        shader.setUniform("model", obj->matrix);
        shader.setUniform("materialColor", obj->materialColor.r, obj->materialColor.g, obj->materialColor.b,
                          obj->materialColor.a);
        shader.setUniform("receiveLight", obj->receiveLight);
        shader.setUniform("useTexture", false);
        if (obj->texture0 != -1) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, obj->texture0);
            shader.setUniform("useTexture", true);
            shader.setUniform("texture0", 0);
        }
        if (obj->texture1 != -1) {
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, obj->texture1);
            shader.setUniform("useTexture", true);
            shader.setUniform("texture1", 1);
        }
        shader.setUniform("ambientStrength", obj->ambientStrength);
        shader.setUniform("shininess", obj->shininess);
        shader.setUniform("specularStrength", obj->specularStrength);
        glDrawElements(GL_TRIANGLES, obj->vertexCount, GL_UNSIGNED_INT, nullptr);
    }
}

void Scene::add(Object *object) {
    objects.push_back(object);
}
