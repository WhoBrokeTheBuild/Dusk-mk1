#ifndef DUSK_OPENGL_H
#define DUSK_OPENGL_H

//#define WIN32_LEAN_AND_MEAN
//#include <Windows.h>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/ext.hpp>

//#pragma comment( lib, "OpenGL32.lib")
//#pragma comment( lib, "GLu32.lib")
//#pragma comment( lib, "glew32.lib")
//#pragma comment( lib, "glfw3.lib")

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat2;
using glm::mat3;
using glm::mat4;
using glm::mat2x2;
using glm::mat2x3;
using glm::mat2x4;
using glm::mat3x2;
using glm::mat3x3;
using glm::mat3x4;
using glm::mat4x2;
using glm::mat4x3;
using glm::mat4x4;

typedef GLuint GLShader;
typedef GLuint GLProgram;
typedef GLuint GLUniformLocation;
typedef GLuint GLTexture;

#endif // DUSK_OPENGL_H
