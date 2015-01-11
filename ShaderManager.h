#ifndef DUSK_SHADER_MANAGER_H
#define DUSK_SHADER_MANAGER_H

#include <string>

#include "OpenGL.h"
#include "ArrayList.h"
#include "Map.h"

using std::string;

struct Shader;

class ShaderManager
{
public:

	inline ShaderManager( void ) :
        m_Programs(),
        m_UniformLocations(),
		m_CurrProg()
	{ }

	virtual inline ~ShaderManager( void )
	{ }

	virtual inline string getClassName( void ) const { return "Shader Manager"; }

	bool loadProgram( const string& name, const ArrayList<Shader>& shaders );

	bool useProgram( const string& name );
	GLint getProgram( const string& name ) { return (m_Programs.containsKey(name) ? m_Programs[name] : -1); }

	inline GLint getUniformLocation( const string& uniformName ) { return getUniformLocation(m_CurrProgName, uniformName); }
	GLint getUniformLocation( const string& programName, const string& uniformName );

    #include "ShaderManager.Uniforms.inc.h"

private:

	void printProgramLog( const GLProgram& program );

	void printShaderLog( const GLShader& shader );

	GLuint loadShaderFromFile( const string& filename, const GLenum& shaderType );

	void checkUniformError( void );

	Map<string, GLProgram> m_Programs;

	Map<string, Map<string, GLUniformLocation>> m_UniformLocations;

	GLProgram m_CurrProg;

	string m_CurrProgName;
};

#endif // DUSK_SHADER_MANAGER_H
