#ifndef CAMERA_H
#define CAMERA_H

#include "glm/gtc/matrix_transform.hpp"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "shader.h"

struct Dimensions;

enum Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera
{
public:
    const float cameraSpeed = 20.f; // adjust accordingly
    float fov = 45.0f;
    
    glm::vec3 cameraPos = glm::vec3(0.0f,0.0f,0.0f);
    // Always looking negative Z
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f,1.0f,0.0f);

    glm::mat4 getView();
    void processInput(GLFWwindow *window, float dt);

private:
    // Recalculate Direction
};

#endif