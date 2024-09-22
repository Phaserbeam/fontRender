#ifndef OBJECT
#define OBJECT
#include <vector>

const unsigned int MAX_OBJECT_SCALE = 16;

class Object
{
public:
    void render();
    void newAttribute(unsigned int size);
    void bindData(std::vector<float> vertices);
    void gen();
    void bind();
    Object();
    ~Object();

private:
    // TOTAL stride
    unsigned int size = 0;
    // TOTAL attributes
    unsigned int index = 0;
    // TOTAL vertices
    unsigned int vertexSize= 0;
    unsigned int VBO;
    unsigned int VAO;
    unsigned int objectScale[MAX_OBJECT_SCALE];
};
#endif