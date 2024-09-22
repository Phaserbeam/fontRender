#ifndef CURVE
#define CURVE
#include <vector>
#include "object.h"
#include "shader.h"
class Curve
{
public:
    Curve(std::vector<float>);
    void bindPoints();
    void render();
    std::vector<float> points;
    Shader shader;
    Object manager;

private:
};
#endif