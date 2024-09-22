#include "bezier.h"
#include "debugger.h"
std::vector<vec2> generateCurve(const vec2 &p1, const vec2 &p2, const vec2 &p3, const vec2 &p4, int res)
{
    std::vector<vec2> curve;
    // <=2000
    //res *= 3;
    for (int i = 0; i <= res; i++)
    {
        double t = i / static_cast<double>(res);
        float x = pow(1 - t, 3) * p1.x + 3 * pow(1 - t, 2) * t * p2.x + 3 * (1 - t) * pow(t, 2) * p3.x + pow(t, 3) * p4.x;
        float y = pow(1 - t, 3) * p1.y + 3 * pow(1 - t, 2) * t * p2.y + 3 * (1 - t) * pow(t, 2) * p3.y + pow(t, 3) * p4.y;
        curve.push_back(vec2(x - .5, y - .5));
        debug(std::to_string(x) + ", " + std::to_string(y));
    }
    return curve;
}

void push(std::vector<float> &vec, vec2 point)
{
    vec.push_back(point.x);
    vec.push_back(point.y);
    vec.push_back(0.0f);
}
vec2 calcTangent(vec2 j, vec2 k)
{
    // [Ay - By]
    // [Bx - Ax]
    return glm::normalize(vec2(j.y - k.y, k.x - j.x));
}
vec2 calcTangents(vec2 i, vec2 j, vec2 k)
{
    vec2 tagent = calcTangent(j, k);

    return glm::normalize((i + tagent) * .5f);
}

void rect(std::vector<float> *curve, vec2 point0, vec2 point1, vec2 aTangent, vec2 bTangent, float width)
{
    aTangent *= width;
    bTangent *= width;
    push(*curve, point0 + aTangent);
    push(*curve, point0 - aTangent);
    push(*curve, point1 + bTangent);
    push(*curve, point1 + bTangent);
    push(*curve, point1 - bTangent);
    push(*curve, point0 - aTangent);
}
// Assumes grouped closely + 2 coordinates per point
std::vector<float> createCurve(std::vector<vec2> points, unsigned int rectCount, float width)
{
    std::vector<float> curve;
    // Loop for N - 1
    bool newLine = true;
    bool lastLine = false;
    vec2 aTangent;
    vec2 bTangent;
    for (int i = 0; i + 1 < points.size(); i++)
    {
        if (i + 3 > points.size())
        {
            lastLine = true;
        }
        vec2 tangent = calcTangent(points[i], points[i + 1]);
        if (newLine)
        {
            newLine = false;
            aTangent = tangent;
        }
        else
        {
            aTangent = calcTangents(tangent, points[i - 1], points[i]);
        }
        if (lastLine)
        {
            bTangent = tangent;
        }
        else
        {
            // Calc the next tangent
            bTangent = calcTangents(tangent, points[i + 1], points[i + 2]);
        }
        rect(&curve, points[i], points[i + 1], aTangent, bTangent, width);
    }
    return curve;
}