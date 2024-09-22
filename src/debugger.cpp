#include "debugger.h"
void glDebug()
{
#ifdef _DEBUG
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cerr << "OPENGL::ERROR::" << error;
    }
#endif
}
void debug(std::string val)
{
#ifdef _DEBUG
    std::cout << val << '\n';
#endif
}

void cDebug(std::string val, int val1, int val2)
{
#ifdef _DEBUG
    if (val1 >= val2)
    {
        debug(val);
    }
#endif
}