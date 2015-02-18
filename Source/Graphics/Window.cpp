#include "Window.h"

#include <Program.h>
#include <Graphics/GraphicsContext.h>
#include <Scripting/ScriptingSystem.h>
#include <World/Camera.h>
#include <Logging/Log.h>

using namespace Dusk::Scripting;
using namespace Dusk::World;
using namespace Dusk::Logging;

Map<GLFWwindow*, Dusk::Graphics::Window*> Dusk::Graphics::g_Windows = Map<GLFWwindow*, Dusk::Graphics::Window*>();

Dusk::Graphics::Window::~Window()
{
    delete mp_GraphicsContext;
    mp_GraphicsContext = nullptr;

    g_Windows.removeKey(mp_GLFWWindow);

    glfwHideWindow(mp_GLFWWindow);
    glfwDestroyWindow(mp_GLFWWindow);
    mp_GLFWWindow = nullptr;
}

bool Dusk::Graphics::Window::init( const unsigned int& width, const unsigned int& height, const string& title, const bool& fullscreen /* = false */ )
{
    LogInfo(getClassName(), "Initializing Window");

	if ( ! glfwInit())
	{
        LogError(getClassName(), "Failed to initialize GLFW");
        return false;
	}

	glfwSetErrorCallback(glfwError);

	glfwWindowHint(GLFW_DEPTH_BITS, 16);

	GLFWmonitor* pMonitor = glfwGetPrimaryMonitor();

    //const GLFWvidmode* mode = glfwGetVideoMode(pMonitor);
    //
    //if (mode->width > 0 && mode->height > 0)
    //{
    //    m_Width = mode->width;
    //    m_Height = mode->height;
    //}

    m_Title = title;
    m_Width = width;
    m_Height = height;
	mp_GLFWWindow = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), (m_Fullscreen ? pMonitor : NULL), NULL);

	if ( ! mp_GLFWWindow )
	{
        LogError(getClassName(), "glfwCreateWindow failed");
        return false;
	}

	mp_GraphicsContext = New GraphicsContext(mp_GLFWWindow);

	g_Windows.add(mp_GLFWWindow, this);

	if (mp_GLFWWindow != nullptr)
	{
		glfwSetFramebufferSizeCallback(mp_GLFWWindow, glfwResize);
		glfwSetKeyCallback(mp_GLFWWindow, glfwKey);
		glfwSetMouseButtonCallback(mp_GLFWWindow, glfwMouse);
		glfwSetCursorPosCallback(mp_GLFWWindow, glfwMouseMove);
		glfwSetScrollCallback(mp_GLFWWindow, glfwMouseScroll);
	}

    return true;
}

bool Dusk::Graphics::Window::resize( const unsigned int& width, const unsigned int& height )
{
    m_Width = width;
    m_Height = height;

    glfwSetWindowSize(mp_GLFWWindow, (int)width, (int)height);

	Program::Inst().getCamera()->resize((float)width, (float)height);

    return true;
}

void Dusk::Graphics::Window::setTitle( const string& title )
{
    m_Title = title;
    glfwSetWindowTitle(mp_GLFWWindow, m_Title.c_str());
}

bool Dusk::Graphics::Window::shouldClose( void )
{
    return ( glfwWindowShouldClose(mp_GLFWWindow) > 0 );
}

Dusk::Graphics::GraphicsContext* Dusk::Graphics::Window::getGraphicsContext( void )
{
    return mp_GraphicsContext;
}

void Dusk::Graphics::Window::hookResize( const int& width, const int& height )
{
	m_Width = width;
	m_Height = height;

	glViewport(0, 0, m_Width, m_Height);
}

void Dusk::Graphics::Window::hookKeyUp( const int& key )
{

}

void Dusk::Graphics::Window::hookKeyDown( const int& key )
{

}

void Dusk::Graphics::Window::hookMouseUp( const int& button )
{

}

void Dusk::Graphics::Window::hookMouseDown( const int& button )
{

}

void Dusk::Graphics::Window::hookMouseMove( const double& x, const double& y )
{

}

void Dusk::Graphics::Window::hookMouseScroll( const double& x, const double& y )
{

}

void Dusk::Graphics::Window::InitScripting( void )
{
	ScriptingSystem* pScriptingSystem = Program::Inst().getScriptingSystem();
	pScriptingSystem->registerFunction("dusk_window_get_width",  &Window::Script_GetWidth);
	pScriptingSystem->registerFunction("dusk_window_get_height", &Window::Script_GetHeight);
	pScriptingSystem->registerFunction("dusk_window_set_width",  &Window::Script_SetWidth);
	pScriptingSystem->registerFunction("dusk_window_set_height", &Window::Script_SetHeight);
	pScriptingSystem->registerFunction("dusk_window_get_title", &Window::Script_GetTitle);
	pScriptingSystem->registerFunction("dusk_window_set_title", &Window::Script_SetTitle);
}

int Dusk::Graphics::Window::Script_GetWidth( lua_State* pState )
{
	Window* pWindow = (Window*)lua_tointeger(pState, 1);
    lua_pushinteger(pState, (int)pWindow->getWidth());

	return 1;
}

int Dusk::Graphics::Window::Script_GetHeight( lua_State* pState )
{
	Window* pWindow = (Window*)lua_tointeger(pState, 1);
    lua_pushinteger(pState, (int)pWindow->getHeight());

	return 1;
}

int Dusk::Graphics::Window::Script_SetWidth( lua_State* pState )
{
	Window* pWindow = (Window*)lua_tointeger(pState, 1);
    int width = lua_tointeger(pState, 2);
    pWindow->setWidth(width);

	return 0;
}

int Dusk::Graphics::Window::Script_SetHeight( lua_State* pState )
{
	Window* pWindow = (Window*)lua_tointeger(pState, 1);
    int height = lua_tointeger(pState, 2);
    pWindow->setHeight(height);

	return 0;
}

int Dusk::Graphics::Window::Script_GetTitle( lua_State* pState )
{
    LogInfo("Test", "Height");
	Window* pWindow = (Window*)lua_tointeger(pState, 1);
    lua_pushstring(pState, pWindow->getTitle().c_str());

	return 1;
}

int Dusk::Graphics::Window::Script_SetTitle( lua_State* pState )
{
	Window* pWindow = (Window*)lua_tointeger(pState, 1);
    string title = lua_tostring(pState, 2);
    pWindow->setTitle(title);

	return 0;
}

void Dusk::Graphics::glfwError( int error, const char* description )
{
    LogErrorFmt("GLFW", "%s (%d)", description, error);
}

void Dusk::Graphics::glfwResize( GLFWwindow* pGLFWWindow, int width, int height )
{
    Window* pWindow = (g_Windows.containsKey(pGLFWWindow) ? g_Windows[pGLFWWindow] : nullptr);
    if (pWindow == nullptr) return;

    pWindow->hookResize(width, height);
}

void Dusk::Graphics::glfwKey( GLFWwindow* pGLFWWindow, int key, int scancode, int action, int mods )
{
    Window* pWindow = (g_Windows.containsKey(pGLFWWindow) ? g_Windows[pGLFWWindow] : nullptr);
    if (pWindow == nullptr) return;

	switch (action)
	{
	case GLFW_PRESS:

        pWindow->hookKeyDown(key);

		break;
	case GLFW_RELEASE:

        pWindow->hookKeyUp(key);

		break;
	case GLFW_REPEAT:


		break;
	}
}

void Dusk::Graphics::glfwMouseMove( GLFWwindow* pGLFWWindow, double x, double y )
{
    Window* pWindow = (g_Windows.containsKey(pGLFWWindow) ? g_Windows[pGLFWWindow] : nullptr);
    if (pWindow == nullptr) return;

    pWindow->hookMouseMove(x, y);
}

void Dusk::Graphics::glfwMouse( GLFWwindow* pGLFWWindow, int button, int action, int mods )
{
    Window* pWindow = (g_Windows.containsKey(pGLFWWindow) ? g_Windows[pGLFWWindow] : nullptr);
    if (pWindow == nullptr) return;

	switch (action)
	{
	case GLFW_PRESS:

        pWindow->hookMouseDown(button);

		break;
	case GLFW_RELEASE:

        pWindow->hookMouseUp(button);

		break;
	}
}

void Dusk::Graphics::glfwMouseScroll( GLFWwindow* pGLFWWindow, double x, double y )
{
    Window* pWindow = (g_Windows.containsKey(pGLFWWindow) ? g_Windows[pGLFWWindow] : nullptr);
    if (pWindow == nullptr) return;

    pWindow->hookMouseScroll(x, y);
}

