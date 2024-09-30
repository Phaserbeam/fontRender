#include "instance.h"
#include "debugger.h"
extern glm::vec2 point;
std::unordered_map<GLFWwindow *, Dimensions *> instanceSizes;
Instance::Instance(Dimensions dimensions) : camera()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 8);

    GLFWwindow *_window = glfwCreateWindow(dimensions.width, dimensions.height, "Collider", nullptr, nullptr);

    if (!_window)
    {
        glfwTerminate();
        std::cout << "Failed to create GLFW window\n";
        return;
    }
    glfwMakeContextCurrent(_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        std::cout << "Failed to initialize GLAD\n";
        return;
    }
    glfwSetWindowUserPointer(_window, this);
    glfwSetFramebufferSizeCallback(_window, [](GLFWwindow *window, int w, int h)
                                   {
                                    debug("Resized Window: " + std::to_string(w) + ", " + std::to_string(h));
        Instance* instance = static_cast<Instance*>(glfwGetWindowUserPointer(window));
        instance->dimensions.width = w;
        instance->dimensions.height = h;
        glViewport(0,0,w,h); });

    glViewport(0, 0, dimensions.width, dimensions.height);
    glfwSwapInterval(1);
    this->window = _window;
}

void Instance::setContext()
{
    glfwMakeContextCurrent(window);
}
void Instance::setProjection(Shader shader)
{
    // camera.projection(shader, dimensions);
}
void Instance::update()
{
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
    {
        using namespace glm;
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);
        xPos = (2.0f * xPos) / (float)(dimensions.width) - 1.0f;
        yPos = 1.0f - (2.0f * yPos) / (float)(dimensions.height);
        // xPos and yPos are now in NDC
        std::cout << "XPOS: " << xPos << " YPOS: " << yPos << '\n';
        // Clip Space, after projection matrix
        vec4 clipRay = vec4((float)xPos, (float)yPos, -1.0f, 1.0f);
        clipRay = inverse(getProjection()) * clipRay;
        clipRay = vec4(vec2(clipRay), -1.0f, 0.0);
        // View Space
        vec3 worldRay = vec3(inverse(getView()) * clipRay);
        worldRay = normalize(worldRay);
        // Find when the ray hits the plane at z = 0.0f
        vec3 origin = camera.cameraPos;
        vec3 normal = vec3(0.0f, 0.0f, 1.0f);
        // vec3 direction = normalize(vec3(directionHomo) / directionHomo.w);

        float denominator = dot(worldRay, normal);
        float numerator = dot(-origin, normal);
        float t = numerator / denominator;
        std::cout << "T: " << t << '\n';
        vec3 intersectionPoint = origin + t * worldRay;
        point = vec2(-intersectionPoint);
        std::cout << "IntersectionPoint: " << -intersectionPoint.x << ", " << -intersectionPoint.y << '\n';
        // solve the system of equations to get T
        // T *Direction + origin = Point at which ray intersects plane
    }
    time.update();
    camera.processInput(window, time.dt);
}
glm::mat4 Instance::getView()
{
    return camera.getView();
}
glm::mat4 Instance::getProjection()
{
    return glm::perspective(camera.fov, dimensions.aspectRatio(), 0.1f, 100.0f);
}
void Instance::addShader(unsigned int id)
{
    std::cout << "Shader Added: " << id << '\n';
    customShaders.push_back(id);
}
void Instance::useShader(unsigned int id)
{
    glUseProgram(customShaders[id]);
}

void Instance::defaultScene(unsigned int id)
{

}