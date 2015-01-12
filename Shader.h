#ifndef DUSK_SHADER_H
#define DUSK_SHADER_H

#include <Arc/ManagedObject.h>
#include "OpenGL.h"
#include <string>

using std::string;

struct Shader :
    public Arc::ManagedObject
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

	virtual inline string getClassName( void ) const { return "Shader"; }

	string Filename;
	GLenum Type;
};

#endif // DUSK_SHADER_H
