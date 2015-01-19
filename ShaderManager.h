#ifndef DUSK_SHADER_MANAGER_H
#define DUSK_SHADER_MANAGER_H

#include <Arc/ManagedObject.h>
#include <Arc/ArrayList.h>
#include <Arc/Map.h>

#include <string>

#include "OpenGL.h"
#include "Math.h"

using std::string;
using Arc::ArrayList;
using Arc::Map;

struct Shader;

class ShaderManager :
    public Arc::ManagedObject
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
	GLProgram getProgram( const string& name ) { return (m_Programs.containsKey(name) ? m_Programs[name] : -1); }

	inline GLUniformLocation getUniformLocation( const string& uniformName ) { return getUniformLocation(m_CurrProgName, uniformName); }
	GLUniformLocation getUniformLocation( const string& programName, const string& uniformName );

    #include "ShaderManager.Uniforms.inc.h"

private:

	void printProgramLog( const GLProgram& program );

	void printShaderLog( const GLShader& shader );

	GLShader loadShaderFromFile( const string& filename, const GLenum& shaderType );

	void checkUniformError( void );

	Map<string, GLProgram> m_Programs;

	Map<string, Map<string, GLUniformLocation>> m_UniformLocations;

	GLProgram m_CurrProg;

	string m_CurrProgName;
};

#endif // DUSK_SHADER_MANAGER_H
