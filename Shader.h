#ifndef DUSK_SHADER_H
#define DUSK_SHADER_H

#include "OpenGL.h"
#include <string>

using std::string;

struct Shader
{
public:

	Shader( const string& filename, const GLenum& type ) :
        Filename(filename),
		Type(type)
	{ }

	Shader( const Shader& rhs ) :
		Filename(rhs.Filename),
		Type(rhs.Type)
	{ }

	void operator=( const Shader& rhs )
	{
		Filename = rhs.Filename;
		Type = rhs.Type;
	}

	string Filename;
	GLenum Type;
};

#endif // DUSK_SHADER_H
