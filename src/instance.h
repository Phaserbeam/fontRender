#ifndef INSTANCE
#define INSTANCE
#include <iostream>
#include <functional>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "camera.h"
#include "shader.h"
struct Dimensions
{
    int width;
    int height;
    float aspectRatio()
    {
        return ((float)width) / ((float)height);
    }
};
struct timeInfo
{
    float dt = 0.0f;
    float lastTime = 0.0f;
    void update()
    {
        dt = glfwGetTime() - lastTime;
        lastTime = glfwGetTime();
    }
};
class Instance
{
public:
    timeInfo time;
    Camera camera;
    GLFWwindow *window;
    Dimensions dimensions;
    // Creates a windows with WIDTH and HEIGHT
    Instance(Dimensions);
    void setContext();
    void update();
    glm::mat4 getView();
    glm::mat4 getProjection();
    void setProjection(Shader shader);

private:
    int index;
};
#endif