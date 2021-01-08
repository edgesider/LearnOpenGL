#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION

#include "Shader.h"
#include "../libs/stb_image.h"
#include "Cube.h"
#include "util.h"
#include "Camera.h"
#include "Scene.h"

//#define SHOW_FPS
#define PERSPECTIVE_CAMERA

static bool paused = false;

void processInput(GLFWwindow *win) {
    if (glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(win, true);

    static bool last_space_pressed = false;
    if (glfwGetKey(win, GLFW_KEY_SPACE) == GLFW_PRESS) {
        if (!last_space_pressed) {
            // keydown
            paused = !paused;
        }
        last_space_pressed = true;
    } else {
        last_space_pressed = false;
    }
}

void printMousePos(GLFWwindow *win) {
    double x, y;
    glfwGetCursorPos(win, &x, &y);
    std::cout << x << ", " << y << std::endl;
}

bool windowMaybeDragging = false;

float mouseSensitivity = 0.01;
float lastX = -1, lastY = -1;
float yaw = 0, pitch = 0;

void onMouseMove(GLFWwindow *win, double x, double y) {
    std::cout << "move: " << x << ", " << y << std::endl;
    printMousePos(win);
    if (!glfwGetWindowAttrib(win, GLFW_FOCUSED))
        return;
    if (lastX == -1) {
        lastX = (float) x;
        lastY = (float) y;
        return;
    }
    yaw -= mouseSensitivity * float(x - lastX);
    pitch -= mouseSensitivity * float(y - lastY);
    if (pitch > 89.9)
        pitch = 89.9;
    else if (pitch < -89.9)
        pitch = -89.9;
    lastX = (float) x;
    lastY = (float) y;
}

void onMouseWheel() {

}

void onFocusChange(GLFWwindow *win, int focus) {
    if (focus == GLFW_TRUE) {
        printMousePos(win);
        lastX = lastY = -1;
//        if (glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
//            glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
//        }
    } else {
    }
}

void render(GLFWwindow *window) {
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);

    Scene scene;
    scene.color = glm::vec4(.15f, .15f, .15f, 0);
    scene.lightColor = glm::vec3(1, 1, 1);

#ifdef PERSPECTIVE_CAMERA
    Camera camera = Camera::perspective(glm::radians(45.0f), 800.0f / 800, 0.1f, 100.0f);
#else
    Camera camera = Camera::orthogonal(-1, 1, -1, 1, 0.1f, 100.0f);
#endif
    camera.position = glm::vec3(0, 8, 4);
    camera.lookAt(glm::vec3(4, 0, 0));

    std::vector<Cube *> cubes;
    auto texture0 = loadTexture("./assets/container.jpg", false);
    auto texture1 = loadTexture("./assets/face.png", true, true);
    const float radius = 4;
    for (int i = 1; i <= 10; i++) {
        auto cube = new Cube;
        float x = radius * (float) std::sin(2 * M_PI / 10 * i),
                z = 4 + radius * (float) std::cos(2 * M_PI / 10 * i);
        cube->position = glm::vec3(x, 0, z);
        cube->rotation.y = 2 * M_PI / 10 * i;
        cube->updateMatrix();
//        cube.matrix = glm::rotate(cube.matrix, (float) glm::acos(1 / sqrt(3)), glm::vec3(-1.0f, 0.0f, 1.0f));
//        cube.updateFromMatrix();
        cube->materialColor = glm::vec4(.6, .2, .4, 0);
        cube->shininess = 64;
        cube->ambientStrength = .7;
        cube->specularStrength = .6;
        cube->texture0 = texture0;
        cube->texture1 = texture1;
        scene.add(cube);
        cubes.push_back(cube);
    }

    Cube light;
    light.receiveLight = false;
    light.materialColor = glm::vec4(1, 1, 1, 0);
    light.position = glm::vec3(0, 2, 1);
    light.updateMatrix();
    light.matrix = glm::scale(light.matrix, glm::vec3(.5, .5, .5));
    scene.add(&light);
    scene.lightPosition = light.position;

    Shader shader("./shaders/vertex.shader", "./shaders/fragment.shader");

    float cubeRotateSpeed, cameraRotateSpeed = 0;

    double lastTime = glfwGetTime(),
            runningTime = 0;
    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(scene.color.r, scene.color.g, scene.color.b, scene.color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        double curr = glfwGetTime(),
                duration = curr - lastTime;
        lastTime = curr;
#ifdef SHOW_FPS
        std::cout << "\r                \r" << "FPS: " << 1.0 / duration;
        std::cout.flush();
#endif
        cubeRotateSpeed = (float) std::cos(curr) * 2;
        if (!paused) {
            runningTime += duration;
//            cube.matrix = glm::rotate(cube.matrix, (float) duration * cubeRotateSpeed, glm::vec3(1, 1, 1));
//            cube.updateFromMatrix();

            for (auto cube : cubes) {
                cube->position = glm::vec3(4, 0, 0);
                cube->rotation.y += cubeRotateSpeed * duration;
                cube->rotation.z += cubeRotateSpeed * duration;
                cube->updateMatrix();
                cube->matrix = glm::translate(cube->matrix, glm::vec3(0, 0, -4));
                cube->updateFromMatrix();
            }
        }
        camera.rotation.y = yaw;
        camera.rotation.x = pitch;
        camera.rotation.z = 0;
        camera.updateMatrix();

        scene.render(shader, camera);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

GLFWwindow *init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    GLFWwindow *window = glfwCreateWindow(800, 800, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    glViewport(0, 0, 800, 800);
    glfwSetFramebufferSizeCallback(window, [](auto win, auto w, auto h) {
        std::cout << w << ' ' << h << std::endl;
        glViewport(0, 0, w, h);
    });

    glfwSetWindowFocusCallback(window, onFocusChange);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, onMouseMove);
//    glfwSetMouseButtonCallback(window, )
    return window;
}

int main() {
    GLFWwindow *window = init();
    if (window == nullptr) {
        return -1;
    }

    try {
        render(window);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        glfwTerminate();
    }

    return 0;
}

uint loadTexture(const std::string &path, bool alpha, bool flipVertical) {
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(flipVertical);
    u_char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (data == nullptr) {
        throw std::runtime_error("failed to load image");
    }

    uint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, alpha ? GL_RGBA : GL_RGB,
                 width, height, 0, alpha ? GL_RGBA : GL_RGB,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
    return texture;
}
