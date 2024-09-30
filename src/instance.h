#ifndef INSTANCE
#define INSTANCE
#include <iostream>
#include <functional>
#include <vector>
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

    // Shader Vectors
    std::vector<unsigned int> customShaders;

    Instance(Dimensions);
    void defaultScene(unsigned int);
    void setContext();
    void update();
    glm::mat4 getView();
    glm::mat4 getProjection();
    void setProjection(Shader shader);
    void addShader(unsigned int);
    void useShader(unsigned int);

private:
    int index;
};
#endif