#include "glm/gtc/matrix_transform.hpp"
#include "shader.h"
#include "camera.h"
#include "instance.h"

glm::mat4 Camera::getView()
{
    glm::mat4 view(1.0f);
    return glm::translate(view, cameraPos);
}
void Camera::processInput(GLFWwindow *window, float dt)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += dt * cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= dt * cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= dt * glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += dt * glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}