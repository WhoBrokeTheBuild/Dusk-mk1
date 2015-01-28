#ifndef DUSK_GRAPHICS_H
#define DUSK_GRAPHICS_H

#include <Arc/Platform.h>

#if defined(ARC_OS_WINDOWS)

#define NOGDI
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#endif // ARC_OS_WINDOWS

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

typedef GLuint GLShader;
typedef GLuint GLProgram;
typedef GLuint GLUniformLocation;
typedef GLuint GLTexture;
typedef GLuint GLAttribute;
typedef GLuint GLBuffer;
typedef GLuint GLVertexArray;
typedef GLenum GLPrimitiveType;

namespace Dusk
{

namespace Graphics
{

} // namespace Graphics

} // namespace Dusk

#endif // DUSK_GRAPHICS_H
