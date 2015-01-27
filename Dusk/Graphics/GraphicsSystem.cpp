#include "GraphicsSystem.h"

#include <Program.h>
#include <Graphics/Window.h>
#include <Graphics/GraphicsContext.h>
#include <Graphics/ShaderManager.h>
#include <Logging/Log.h>

using namespace Dusk::Logging;

Dusk::Graphics::GraphicsSystem::~GraphicsSystem()
{
    delete mp_ShaderManager;
    mp_ShaderManager = nullptr;

    delete mp_Window;
    mp_Window = nullptr;
}

bool Dusk::Graphics::GraphicsSystem::init(const unsigned int& width, const unsigned int& height, const string& title, const bool& fullscreen /* = false */ , const bool& vsync /* = false */ )
{
    mp_Window = New Window();
    if ( ! mp_Window->init(width, height, title, fullscreen))
    {
        LogError(getClassName(), "Failed to initialize Window");
        return false;
    }

    getGraphicsContext()->bind();

    glfwSwapInterval( ( vsync ? 1 : 0) );

    glewExperimental = GL_TRUE;
	GLenum ret = glewInit();
	if (ret != GLEW_OK)
	{
		LogErrorFmt(getClassName(), "Failed to initialize GLEW (Error #%d, %s)", ret, glewGetErrorString(ret));
        return false;
	}

	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	mp_ShaderManager = New ShaderManager();

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
