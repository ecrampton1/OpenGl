#ifndef __RENDERER__HPP__
#define __RENDERER__HPP__

#include <GL/glew.h>
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"



//OPenGL Callback taken from khronos.org/opengl/wiki/opengl_error
void GLAPIENTRY
MessageCallback(GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam);


//singleton or static.....
class Renderer
{
public:
    //Renderer();
    //~Renderer();
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
    void clear();


};



#endif
