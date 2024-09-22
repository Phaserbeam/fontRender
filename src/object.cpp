#include "glad/glad.h"
#include <iostream>
#include "object.h"
#include "debugger.h"
void Object::render()
{
#ifdef _DEBUG
    if (vertexSize == 0)
    {
        std::cerr << "ERROR:OBJECT:VERTICES_NULL";
    }
#endif
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertexSize / size);
}
Object::Object()
{
    // Generate and bind VBOS
    gen();
    bind();
}
void Object::bind()
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glDebug();
}

void Object::gen()
{
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glDebug();
}

void Object::newAttribute(unsigned int scale)
{
    bind();
    cDebug("ERROR::OBJECT::RAN_OUT_OF_SPACE", index, MAX_OBJECT_SCALE);

    objectScale[index] = scale;
    size += scale;

    unsigned int strideSize = 0;

    for (unsigned int i = 0; i <= index; i++)
    {
        glVertexAttribPointer(i, objectScale[i], GL_FLOAT, GL_FALSE, size * sizeof(float), (void *)(strideSize * sizeof(float)));
        glDebug();
        strideSize += objectScale[i];
    }

    glEnableVertexAttribArray(index);
    index++;
}

void Object::bindData(std::vector<float> vertices)
{
    bind();
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glDebug();
    vertexSize = vertices.size();
    glDebug();
    debug(std::string("Vertex Size: " + std::to_string(vertexSize)));
}

Object::~Object()
{
    glDeleteVertexArrays(1, &VAO);
}