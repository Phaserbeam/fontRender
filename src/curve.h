#ifndef CURVE
#define CURVE
#include <vector>
#include "object.h"
#include "shader.h"
class Curve
{
public:
    unsigned int shaderID;
    Curve();
    void bindPoints(std::vector<float>);
    void setShader(unsigned int);
    void render();
    std::vector<float> points;
    Object manager;
private:
};
#endif