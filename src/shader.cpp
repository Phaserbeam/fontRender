#include "shader.h"

void Shader::shaders(std::string vertexPath, std::string fragmentPath)
{
    vertexPath = path + vertexPath;
    fragmentPath = path + fragmentPath;
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vertexFile;
    std::ifstream fragmentFile;
    vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        // Open up the files
        vertexFile.open(vertexPath);
        fragmentFile.open(fragmentPath);

        std::stringstream vStream, fStream;
        vStream << vertexFile.rdbuf();
        fStream << fragmentFile.rdbuf();
        vertexFile.close();
        fragmentFile.close();

        vertexCode = vStream.str();
        fragmentCode = fStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "PATHS: " << vertexPath << ", " << fragmentPath << "\n";
        std::cout << "ERROR:SHADER: Error reading from file\n";
    }
    const char *vShaderSource = vertexCode.c_str();
    const char *fShaderSource = fragmentCode.c_str();

    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    // Vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderSource, nullptr);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        std::cout << "ERROR:SHADER:VERTEX:COMPILATION: " << infoLog << '\n';
    }
    // Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderSource, nullptr);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        std::cout << "ERROR:SHADER:FRAGMENT:COMPILATION: " << infoLog << '\n';
    }

    // Shader Program
    shader = glCreateProgram();
    glAttachShader(shader, vertex);
    glAttachShader(shader, fragment);
    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "ERROR:SHADER:LINKING: " << infoLog << '\n';
    }
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    glUseProgram(shader);
}

void Shader::use() const
{
    glUseProgram(shader);
}

void Shader::setBool(const std::string &name, bool val) const
{
    use();
    glUniform1ui(glGetUniformLocation(shader, name.c_str()), val);
}

void Shader::setInt(const std::string &name, int val) const
{
    use();
    glUniform1i(glGetUniformLocation(shader, name.c_str()), val);
}

void Shader::setFloat(const std::string &name, float val) const
{
    use();
    glUniform1f(glGetUniformLocation(shader, name.c_str()), val);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &val) const
{
    use();
    glUniform3fv(glGetUniformLocation(shader, name.c_str()), 1, &val[0]);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &val) const
{
    use();
    glUniformMatrix4fv(glGetUniformLocation(shader, name.c_str()), 1, GL_FALSE, &val[0][0]);
}