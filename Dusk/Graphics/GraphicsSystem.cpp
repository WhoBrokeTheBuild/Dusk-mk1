#include "GraphicsSystem.h"

#include <Program.h>
#include <Graphics/Window.h>
#include <Graphics/GraphicsContext.h>
#include <Graphics/ShaderManager.h>
#include <Scripting/ScriptingSystem.h>
#include <Logging/Log.h>

using namespace Dusk::Scripting;
using namespace Dusk::Logging;

const Dusk::Events::EventID Dusk::Graphics::GraphicsSystem::EVT_RESET  = 1;

Dusk::Graphics::GraphicsSystem::~GraphicsSystem()
{
    delete mp_ShaderManager;
    mp_ShaderManager = nullptr;

    delete mp_Window;
    mp_Window = nullptr;

    glfwTerminate();
}

bool Dusk::Graphics::GraphicsSystem::init(const unsigned int& width, const unsigned int& height, const string& title, const bool& fullscreen /* = false */, const bool& vsnyc /* = false */  )
{
	if ( ! glfwInit())
	{
        LogError(getClassName(), "Failed to initialize GLFW");
        return false;
	}

    LogInfoFmt(getClassName(), "Running GLFW Version %s", glfwGetVersionString());

	glfwSetErrorCallback(glfwError);

    m_Vsync = vsnyc;
    mp_Window = New Window();
    if ( ! mp_Window->init(width, height, title, fullscreen))
    {
        LogError(getClassName(), "Failed to initialize Window");
        return false;
    }

    getWindow()->getGraphicsContext()->bind();

    initGL();

	mp_ShaderManager = New ShaderManager();

	return true;
}

bool Dusk::Graphics::GraphicsSystem::initGL( void )
{
    glfwSwapInterval( ( m_Vsync ? 1 : 0) );

    glewExperimental = GL_TRUE;
	GLenum ret = glewInit();
	if (ret != GLEW_OK)
	{
		LogErrorFmt(getClassName(), "Failed to initialize GLEW (Error #%d, %s)", ret, glewGetErrorString(ret));
        return false;
	}

    LogInfoFmt(getClassName(), "Running GLEW Version %s", glewGetString(GLEW_VERSION));
	LogInfoFmt(getClassName(), "Running OpenGL Version %s", glGetString(GL_VERSION));
	LogInfoFmt(getClassName(), "Running OpenGL Shading Language Version %s", glGetString(GL_SHADING_LANGUAGE_VERSION));

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	return true;
}

Dusk::Graphics::Window* Dusk::Graphics::GraphicsSystem::getWindow(void)
{
    return mp_Window;
}

Dusk::Graphics::GraphicsContext* Dusk::Graphics::GraphicsSystem::getGraphicsContext(void)
{
    return (mp_Window == nullptr ? nullptr : mp_Window->getGraphicsContext());
}

Dusk::Graphics::ShaderManager* Dusk::Graphics::GraphicsSystem::getShaderManager(void)
{
    return mp_ShaderManager;
}

void Dusk::Graphics::GraphicsSystem::handleReset( const Event& event )
{
    initGL();
    dispatch(Event(GraphicsSystem::EVT_RESET));
}

void Dusk::Graphics::GraphicsSystem::InitScripting( void )
{
	ScriptingSystem* pScriptingSystem = Program::Inst()->getScriptingSystem();
	pScriptingSystem->registerFunction("dusk_graphics_system_get_window",           &GraphicsSystem::Script_GetWindow);
	pScriptingSystem->registerFunction("dusk_graphics_system_get_graphics_context", &GraphicsSystem::Script_GetGraphicsContext);
	pScriptingSystem->registerFunction("dusk_graphics_system_get_shader_manager",   &GraphicsSystem::Script_GetShaderManager);

	Window::InitScripting();
	ShaderManager::InitScripting();
}

int Dusk::Graphics::GraphicsSystem::Script_GetWindow( lua_State* pState )
{
    lua_pushinteger(pState, (unsigned long)Program::Inst()->getGraphicsSystem()->getWindow());

	return 1;
}

int Dusk::Graphics::GraphicsSystem::Script_GetGraphicsContext( lua_State* pState )
{
    lua_pushinteger(pState, (unsigned long)Program::Inst()->getGraphicsSystem()->getGraphicsContext());

	return 1;
}

int Dusk::Graphics::GraphicsSystem::Script_GetShaderManager( lua_State* pState )
{
    lua_pushinteger(pState, (unsigned long)Program::Inst()->getGraphicsSystem()->getShaderManager());

	return 1;
}

void Dusk::Graphics::glfwError( int error, const char* description )
{
    LogErrorFmt("GLFW", "%s (%d)", description, error);
}
