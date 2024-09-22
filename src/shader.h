#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

class Shader
{
public:
    unsigned int shader;
    const std::string path = "/home/Zyp/Documents/computing/c++/fontRender/shaders/";

    void use() const;
    void shaders(std::string vPath, std::string fPath);
    // Uniform Utility functions
    void setBool(const std::string &name, bool val) const;
    void setInt(const std::string &name, int val) const;
    void setFloat(const std::string &name, float val) const;
    void setVec3(const std::string &name, const glm::vec3 &val) const;
    void setMat4(const std::string &name, const glm::mat4 &val) const;
};

#endif