#ifndef DUSK_OPENGL_H
#define DUSK_OPENGL_H

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

#endif // DUSK_OPENGL_H
