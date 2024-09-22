#ifndef BEZIER
#define BEZIER
#include <vector>
#include <iostream>
#include "glm/glm.hpp"
using glm::vec2;

std::vector<float> createCurve(std::vector<vec2> points, unsigned int rectCount, float width);
std::vector<vec2> generateCurve(const vec2& p1,const vec2& p2,const vec2& p3, const vec2& p4, int res);
vec2 calcTangent(vec2 j, vec2 k);
void push(std::vector<float> &vec, vec2 point);
// -----------------------------------------------
// Creates a set of points as a cubic bezier curve
#endif