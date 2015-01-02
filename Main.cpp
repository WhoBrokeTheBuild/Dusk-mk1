#include <cstdio>
#include <string>
#include <GLFW/glfw3.h>

using std::string;

void error( const string& msg, const bool& fatal = true )
{
    printf("Error: %s\n", msg.c_str());
    if (fatal)
        exit(1);
}

void glfwError( int error, const char* description )
{
}

void glfwResize( GLFWwindow* window, int width, int height )
{
}

void glfwKey( GLFWwindow* window, int key, int scancode, int action, int mods )
{
	switch (action)
	{
	case GLFW_PRESS:


		break;
	case GLFW_RELEASE:


		break;
	case GLFW_REPEAT:


		break;
	}
}

void glfwMouseMove( GLFWwindow* window, double x, double y )
{
}

void glfwMouse( GLFWwindow* window, int button, int action, int mods )
{
	switch (action)
	{
	case GLFW_PRESS:


		break;
	case GLFW_RELEASE:


		break;
	}
}

void glfwMouseScroll( GLFWwindow* window, double x, double y )
{
}

int main(int argc, char* argv[])
{
	if ( ! glfwInit())
        error("Failed to initialize GLFW");

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

	GLFWwindow* pWindow = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), (m_Fullscreen ? pMonitor : NULL), NULL);

	if ( ! pWindow )
	{
        error("Failed to create GLFW Window");
	}

	glfwMakeContextCurrent(pWindow);

	glfwSwapInterval(0);

	//glewExperimental = GL_TRUE;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);

	//glEnable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (pWindow != nullptr)
	{
		glfwSetFramebufferSizeCallback(pWindow, glfwResize);
		glfwSetKeyCallback(pWindow, glfwKey);
		glfwSetMouseButtonCallback(pWindow, glfwMouse);
		glfwSetCursorPosCallback(pWindow, glfwMouseMove);
		glfwSetScrollCallback(pWindow, glfwMouseScroll);
	}

	float m_LastFrameTime = 0.0f;

	while( ! glfwWindowShouldClose(pWindow) )
	{
		const float updateInt = 1.0f / 60.0f;
		static float updateTimer = 0.0f;

		double currTime = glfwGetTime();
		float deltaTime = (float)(currTime - m_LastFrameTime);
		m_LastFrameTime = currTime;

		updateTimer += deltaTime;

		if (updateTimer >= updateInt)
		{
			updateTimer = 0.0f;
			deltaTime = updateInt; // Actual time since last update/render

			//update(deltaTime);
			//render();
			glfwSwapBuffers(pWindow);
		}

		glfwPollEvents();
	}

    return 0;
}
