#include "curve.h"
#include <iostream>

Curve::Curve()
{
    manager.newAttribute(3);
}
void Curve::bindPoints(std::vector<float> vertices)
{
    points = vertices;
    manager.bindData(points);
}

void Curve::render()
{
    manager.render();
}
void Curve::setShader(unsigned int id)
{
    shaderID = id;
}