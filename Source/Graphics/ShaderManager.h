#ifndef DUSK_SHADER_MANAGER_H
#define DUSK_SHADER_MANAGER_H

#include <Arc/ManagedObject.h>
#include <Arc/ArrayList.h>
#include <Arc/Map.h>

#include <string>

#include <Graphics/Graphics.h>
#include <Scripting/Scripting.h>
#include <Math/Math.h>

using std::string;
using Arc::ArrayList;
using Arc::Map;

namespace Dusk
{

namespace Graphics
{

struct ShaderInfo :
    public Arc::ManagedObject
{
public:

	ShaderInfo( const GLenum& type, const string& filename ) :
		Type(type),
		Filename(filename)
	{ }

	ShaderInfo( const ShaderInfo& rhs ) :
		Type(rhs.Type),
		Filename(rhs.Filename)
	{ }

	void operator=( const ShaderInfo& rhs )
	{
		Type = rhs.Type;
		Filename = rhs.Filename;
	}

	virtual inline string getClassName( void ) const { return "Shader Info"; }

	GLenum Type;
	string Filename;

}; // struct ShaderInfo

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

	bool loadProgram( const string& name, const ArrayList<ShaderInfo>& shaders );
	bool useProgram( const string& name );

	inline GLUniformLocation getUniformLocation( const string& uniformName ) { return getUniformLocation(m_CurrProgName, uniformName); }
	GLUniformLocation getUniformLocation( const string& programName, const string& uniformName );

    #include "ShaderManager.Uniforms.inc.h"

	static void InitScripting( void );
	static int Script_LoadProgram( lua_State* pState );

private:

	void printProgramLog( const GLProgram& program );

	void printShaderLog( const GLShader& shader );

	GLShader loadShaderFromFile( const string& filename, const GLenum& shaderType );

	void checkUniformError( void );

	Map<string, GLProgram> m_Programs;

	Map<string, Map<string, GLUniformLocation>> m_UniformLocations;

	GLProgram m_CurrProg;

	string m_CurrProgName;

}; // class ShaderManager

} // Graphics

} // Dusk

#endif // DUSK_SHADER_MANAGER_H
