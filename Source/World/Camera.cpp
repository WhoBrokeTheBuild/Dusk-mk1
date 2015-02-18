#include "Camera.h"

#undef far
#undef near

#include <Program.h>
#include <Scripting/ScriptingSystem.h>

using namespace Dusk::Scripting;

mat4x4 Dusk::World::Camera::getViewMatrix( void )
{
    if ( ! m_ViewUpdated)
        return m_View;

    m_ViewUpdated = false;

	m_View = glm::lookAt(getPos(), getPos() + getDir(), getUp());

	return m_View;
}

void Dusk::World::Camera::setPerspective( const GLfloat& fov, const GLfloat& width, const GLfloat& height, const GLfloat& near, const GLfloat& far )
{
	m_FOV = fov;
	m_AspectWidth = width;
	m_AspectHeight = height;
	m_Near = near;
	m_Far = far;
	m_ProjUpdated = true;
}

mat4x4 Dusk::World::Camera::getProjectionMatrix( void )
{
	if ( ! m_ProjUpdated)
		return m_Proj;

	if (m_AspectWidth <= 0.0f || m_AspectHeight <= 0.0f || m_FOV <= 0.0f)
		return mat4(1.0f);

	m_Proj = glm::perspectiveFov(m_FOV, m_AspectWidth, m_AspectHeight, m_Near, m_Far);

	return m_Proj;
}

void Dusk::World::Camera::resize(GLfloat width, GLfloat height)
{
	m_AspectWidth = width;
	m_AspectHeight = height;
	m_ProjUpdated = true;
}

void Dusk::World::Camera::InitScripting( void )
{
	ScriptingSystem* pScriptingSystem = Program::Inst().getScriptingSystem();
	pScriptingSystem->registerFunction("dusk_camera_get_pos",  &Camera::Script_GetPos);
}

int Dusk::World::Camera::Script_GetPos( lua_State* pState )
{
	Camera* pCamera = (Camera*)lua_tointeger(pState, 1);
	const vec3& pos = pCamera->getPos();

	lua_newtable(pState);

	lua_pushstring(pState, "x");
	lua_pushnumber(pState, pos.x);
	lua_settable(pState, -3);

	lua_pushstring(pState, "y");
	lua_pushnumber(pState, pos.y);
	lua_settable(pState, -3);

	lua_pushstring(pState, "z");
	lua_pushnumber(pState, pos.z);
	lua_settable(pState, -3);

    return 1;
}

int Dusk::World::Camera::Script_SetPos( lua_State* pState )
{
	Camera* pCamera = (Camera*)lua_tointeger(pState, 1);

    return 0;
}

int Dusk::World::Camera::Script_GetDir( lua_State* pState )
{
	Camera* pCamera = (Camera*)lua_tointeger(pState, 1);

    return 1;
}

int Dusk::World::Camera::Script_SetDir( lua_State* pState )
{
	Camera* pCamera = (Camera*)lua_tointeger(pState, 1);

    return 0;
}
