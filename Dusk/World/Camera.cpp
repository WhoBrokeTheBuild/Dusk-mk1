#include "Camera.h"

#undef far
#undef near

#include <Program.h>
#include <Graphics/GraphicsSystem.h>
#include <Graphics/Window.h>
#include <Scripting/ScriptingSystem.h>

using namespace Dusk::Scripting;
using namespace Dusk::Graphics;

Dusk::World::Camera::Camera( const unsigned int& width, const unsigned int& height, const vec3& pos, const vec3& dir,
               const vec3& up, const GLfloat& fov, const GLfloat& near, const GLfloat& far )
    : m_ProjUpdated		(true),
      m_ViewUpdated     (true),
      m_Width   		(width),
      m_Height	        (height),
      m_FOV             (fov),
      m_Near            (near),
      m_Far             (far),
      m_Pos             (pos),
      m_Dir             (dir),
      m_Up              (up),
      m_Orient			(1, 0, 0, 0)
{
    Program::Inst()->getGraphicsSystem()->getWindow()->addEventListener(Window::EVT_RESIZE, this, &Camera::handleWindowResize);
}

mat4x4 Dusk::World::Camera::getViewMatrix( void )
{
    if ( ! m_ViewUpdated)
        return m_View;

    m_ViewUpdated = false;

	m_View = glm::lookAt(getPos(), getPos() + getDir(), getUp());

	return m_View;
}

void Dusk::World::Camera::setPerspective( const GLfloat& fov, const unsigned int& width, const unsigned int& height, const GLfloat& near, const GLfloat& far )
{
	m_FOV = fov;
	m_Width = width;
	m_Height = height;
	m_Near = near;
	m_Far = far;
	m_ProjUpdated = true;
}

mat4x4 Dusk::World::Camera::getProjectionMatrix( void )
{
	if ( ! m_ProjUpdated)
		return m_Proj;

	if (m_Width <= 0 || m_Height <= 0 || m_FOV <= 0.0f)
		return mat4(1.0f);

	m_Proj = glm::perspectiveFov(m_FOV, (GLfloat)m_Width, (GLfloat)m_Height, m_Near, m_Far);

	return m_Proj;
}

void Dusk::World::Camera::resize(const unsigned int& width, const unsigned int& height)
{
	m_Width = width;
	m_Height = height;
	m_ProjUpdated = true;
}

void Dusk::World::Camera::handleWindowResize( const Event& event )
{
    const WindowResizeEventData* pData = event.getDataAs<WindowResizeEventData>();
    resize(pData->getWidth(), pData->getHeight());
}

void Dusk::World::Camera::InitScripting( void )
{
	ScriptingSystem* pScriptingSystem = Program::Inst()->getScriptingSystem();
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
