#include "curve.h"
#include <iostream>

Curve::Curve(std::vector<float> vertices)
{
    points = vertices;
}
void Curve::bindPoints()
{
    manager.bindData(points);
}

void Curve::render()
{
    shader.use();
    manager.render();
}