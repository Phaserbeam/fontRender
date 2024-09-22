#include <iostream>
#include <vector>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "instance.h"
#include "curve.h"
#include "bezier.h"
#include "glm/glm.hpp"
#include "debugger.h"
glm::vec2 point = glm::vec2(0.0f, 0.0f);
int main()
{
    Instance instance({400, 400});
    std::vector<float> vertices = createCurve(generateCurve(point, glm::vec2(0.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec2(1.0f, 0.0f), 20), 1, .05f);

    Curve curve(vertices);
    curve.bindPoints();
    curve.manager.newAttribute(3);
    curve.shader.shaders("vertex.glsl", "fragment.glsl");

    while (!glfwWindowShouldClose(instance.window))
    {
        glfwPollEvents();
        instance.update();
        glClearColor(0.415686f, 0.184314f, 0.47451f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(point, 0.0f));
        model = glm::scale(model, glm::vec3(2.5f)); // Scale it up
        curve.shader.setMat4("model", model);
        curve.shader.setMat4("view", instance.getView());
        curve.shader.setMat4("projection", instance.getProjection());

        curve.render();

        glfwSwapBuffers(instance.window);
    }
    glfwTerminate();
}