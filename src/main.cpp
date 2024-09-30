#include <iostream>
#include <vector>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "instance.h"
#include "curve.h"
#include "bezier.h"
#include "glm/glm.hpp"
#include "debugger.h"

glm::vec2 point(0.0f);
int main()
{
    Instance instance({400, 400});
    Shader testShader;
    testShader.shaders("vertex.glsl", "fragment.glsl");
    instance.addShader(testShader.shader);
    std::vector<float> vertices = createCurve(generateCurve(glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec2(1.0f, 0.0f), 5), 1, .05f);

    Curve curve;

    curve.bindPoints(vertices);
    glUseProgram(testShader.shader);
    std::cout << testShader.shader << '\n';
    std::vector<float> verts = {
        // first triangle
        0.5f, 0.5f, 0.0f,   // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, 0.5f, 0.0f,  // top le  // second triangle
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f,  // top left
    };

    Curve line;
    line.bindPoints(verts);
    while (!glfwWindowShouldClose(instance.window))
    {
        //glUseProgram(instance.customShaders[0]);
        glfwPollEvents();
        // Camera, DT, Mouse etc
        instance.update();
        glClearColor(0.415686f, 0.184314f, 0.47451f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        testShader.setMat4("view", instance.getView());
        testShader.setMat4("projection", instance.getProjection());
        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(point, 0.0f));
        model = glm::scale(model, glm::vec3(2.5f)); // Scale it up
        testShader.setMat4("model", model);

        curve.render();
        testShader.setMat4("model", glm::mat4(1.0f));
        line.render();

        glfwSwapBuffers(instance.window);
    }
    glfwTerminate();
}