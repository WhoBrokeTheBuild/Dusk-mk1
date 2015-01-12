#include "Program.h"

#include "Log.h"
#include "TimeInfo.h"
#include "ShaderManager.h"
#include "Shader.h"

Program::~Program()
{
}

void Program::start()
{
    LogInfo(getClassName(), "Starting");

    if ( ! init())
    {
        LogError(getClassName(), "Initializing failed");
    }

    if ( ! load())
    {
        LogError(getClassName(), "Loading assets failed");
        return;
    }

	float lastFrameTime = 0.0f;
	TimeInfo timeInfo;

	while( ! glfwWindowShouldClose(mp_Window) )
	{
		const float updateInt = 1.0f / 60.0f;
		float updateTimer = 0.0f;

		double currTime = glfwGetTime();
		float elapsedTime = (float)(currTime - lastFrameTime);
		lastFrameTime = currTime;

		updateTimer += elapsedTime;

        timeInfo.ElapsedSeconds = elapsedTime;
        timeInfo.ElapsedMilliseconds = timeInfo.ElapsedSeconds * 1000.0f;
        timeInfo.TotalSeconds += elapsedTime;
        timeInfo.TotalMilliseconds += timeInfo.ElapsedMilliseconds;

        timeInfo.Delta = timeInfo.ElapsedMilliseconds / updateInt;

		if (updateTimer >= updateInt)
		{
			updateTimer = 0.0f;

            update(timeInfo);
			render();
			glfwSwapBuffers(mp_Window);
		}

		glfwPollEvents();
	}
}

bool Program::init()
{
    LogInfo(getClassName(), "Initializing");

    if ( ! initWindow())
    {
        LogError(getClassName(), "Failed to create window");
        return false;
    }

    return true;
}

bool Program::load()
{
    LogInfo(getClassName(), "Loading Resources");

    ArrayList<Shader> flatShaderList;
    flatShaderList.add(Shader("Shaders/flat.fs.glsl", GL_FRAGMENT_SHADER));
    flatShaderList.add(Shader("Shaders/flat.vs.glsl", GL_VERTEX_SHADER));
    getShaderManager()->loadProgram("flat", flatShaderList);

    return true;
}

void Program::update(const TimeInfo& timeInfo)
{
}

void Program::render()
{
}

bool Program::initWindow()
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

    bool m_Fullscreen = false;
    int m_Width = 800, m_Height = 600;
    string m_Title = "Dusk Engine - Test";

	if (m_Fullscreen)
	{
		const GLFWvidmode* mode = glfwGetVideoMode(pMonitor);

		if (mode->width > 0 && mode->height > 0)
		{
			m_Width = mode->width;
			m_Height = mode->height;
		}
	}

	mp_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), (m_Fullscreen ? pMonitor : NULL), NULL);

	if ( ! mp_Window )
	{
        LogError(getClassName(), "glfwCreateWindow failed");
        return false;
	}

	glfwMakeContextCurrent(mp_Window);

	glfwSwapInterval(0);

    glewExperimental = GL_TRUE;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);

	//glEnable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (mp_Window != nullptr)
	{
		glfwSetFramebufferSizeCallback(mp_Window, glfwResize);
		glfwSetKeyCallback(mp_Window, glfwKey);
		glfwSetMouseButtonCallback(mp_Window, glfwMouse);
		glfwSetCursorPosCallback(mp_Window, glfwMouseMove);
		glfwSetScrollCallback(mp_Window, glfwMouseScroll);
	}

	return true;
}

void Program::hookResize( const int& width, const int& height )
{

}

void Program::hookKeyUp( const int& key )
{

}

void Program::hookKeyDown( const int& key )
{

}

void Program::hookMouseUp( const int& button )
{

}

void Program::hookMouseDown( const int& button )
{

}

void Program::hookMouseMove( const double& x, const double& y )
{

}

void Program::hookMouseScroll( const double& x, const double& y )
{

}

void glfwError( int error, const char* description )
{
    LogErrorFmt("GLFW", "%s (%d)", description, error);
}

void glfwResize( GLFWwindow* window, int width, int height )
{
    Program::getInstance().hookResize(width, height);
}

void glfwKey( GLFWwindow* window, int key, int scancode, int action, int mods )
{
	switch (action)
	{
	case GLFW_PRESS:

        Program::getInstance().hookKeyDown(key);

		break;
	case GLFW_RELEASE:

        Program::getInstance().hookKeyUp(key);

		break;
	case GLFW_REPEAT:


		break;
	}
}

void glfwMouseMove( GLFWwindow* window, double x, double y )
{
    Program::getInstance().hookMouseMove(x, y);
}

void glfwMouse( GLFWwindow* window, int button, int action, int mods )
{
	switch (action)
	{
	case GLFW_PRESS:

        Program::getInstance().hookMouseDown(button);

		break;
	case GLFW_RELEASE:

        Program::getInstance().hookMouseUp(button);

		break;
	}
}

void glfwMouseScroll( GLFWwindow* window, double x, double y )
{
    Program::getInstance().hookMouseScroll(x, y);
}
