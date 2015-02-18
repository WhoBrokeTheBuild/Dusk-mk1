#ifndef DUSK_CAMERA_H
#define DUSK_CAMERA_H

#include <Arc/ManagedObject.h>

#include <Graphics/Graphics.h>
#include <Scripting/Scripting.h>
#include <Math/Math.h>

#define _USE_MATH_DEFINES
#include <cmath>

namespace Dusk
{

namespace World
{

class Camera :
    public Arc::ManagedObject
{
public:

	inline Camera( const GLfloat& width, const GLfloat& height, const vec3& pos, const vec3& dir, const vec3& up,
                   const GLfloat& fov, const GLfloat& near, const GLfloat& far )
		: m_ProjUpdated		(true),
          m_ViewUpdated     (true),
		  m_FOV             (fov),
		  m_AspectWidth		(width),
		  m_AspectHeight	(height),
		  m_Near            (near),
		  m_Far             (far),
		  m_Pos             (pos),
		  m_Dir             (dir),
		  m_Up              (up),
		  m_Orient			(1, 0, 0, 0)
	{
    }

	virtual inline ~Camera( void ) { }

	virtual inline string getClassName( void ) const { return "Camera"; }

	void resize( GLfloat width, GLfloat height );

	inline vec3 getPos( void ) const      { return m_Pos; }
	inline void setPos( const vec3& pos ) { setPos(pos.x, pos.y, pos.z); }
	inline void setPos( const GLfloat& x, const GLfloat& y, const GLfloat& z )
	{
		m_Pos.x = x;
		m_Pos.y = y;
		m_Pos.z = z;
        m_ViewUpdated = true;
	}

	inline vec3 getDir( void ) const	  { return m_Dir; }
	inline void setDir( const vec3& dir ) { setDir(dir.x, dir.y, dir.z); }
	inline void setDir( const GLfloat& x, const GLfloat& y, const GLfloat& z )
	{
        m_Dir.x = x;
        m_Dir.y = y;
        m_Dir.z = z;
        m_ViewUpdated = true;
	}

	inline vec3 getUp( void ) const     { return m_Up; }
	inline void setUp( const vec3& up ) { setUp(up.x, up.y, up.z); }
	inline void setUp( const GLfloat& x, const GLfloat& y, const GLfloat& z )
	{
		m_Up.x = x;
		m_Up.y = y;
		m_Up.z = z;
        m_ViewUpdated = true;
	}

	inline vec3 getLeft( void )  { return cross(m_Up, getDir()); }
	inline vec3 getRight( void ) { return cross(getDir(), m_Up); }

	inline GLfloat getFOV( void ) const { return m_FOV; }
	inline void setFOV( const GLfloat& fov )
	{
		m_FOV = fov;
		m_ProjUpdated = true;
	}

	inline void setAspect( const GLfloat& width, const GLfloat& height )
	{
		m_AspectWidth = width;
		m_AspectHeight = height;
		m_ProjUpdated = true;
	}

	inline void lookAt( const vec3& center )
	{
        m_Dir = center - m_Pos;
	}

	void setPerspective( const GLfloat& fov, const GLfloat& width, const GLfloat& height, const GLfloat& vNear, const GLfloat& vFar );

	mat4x4 getViewMatrix( void );
	mat4x4 getProjectionMatrix( void );

	static void InitScripting( void );
	static int Script_GetPos( lua_State* pState );
	static int Script_SetPos( lua_State* pState );
	static int Script_GetDir( lua_State* pState );
	static int Script_SetDir( lua_State* pState );

private:

	bool			m_ProjUpdated,
                    m_ViewUpdated;

	GLfloat			m_FOV,
					m_AspectWidth,
					m_AspectHeight,
					m_Near,
					m_Far,
					m_Pitch,
					m_Yaw;

	mat4x4			m_View,
					m_Proj;

	vec3			m_Pos,
					m_Dir,
					m_Up,
					m_LookAt;

	quat			m_Orient;

}; // class Camera

} // namespace World

} // namespace Dusk

#endif // DUSK_CAMERA_H
