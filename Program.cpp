#include "Program.h"

#include "Log.h"
#include "TimeInfo.h"
#include "ShaderManager.h"
#include "Shader.h"
#include "Camera.h"

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

    float updateTimer = 0.0f;
	while( ! glfwWindowShouldClose(mp_Window) )
	{
		const float updateInt = 1.0f / 60.0f;

		float currTime = (float)glfwGetTime();
		float elapsedTime = currTime - lastFrameTime;
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

	term();
}

bool Program::init()
{
    LogInfo(getClassName(), "Initializing");

    if ( ! initWindow())
    {
        LogError(getClassName(), "Failed to create window");
        return false;
    }

	mp_ShaderManager = New ShaderManager();
    mp_Camera = New Camera((float)m_Width, (float)m_Height, vec3(3.0f, 3.0f, 3.0f), vec3(-1.0f), vec3(0.0f, 1.0f, 0.0f), 45.0f, 0.1f, 10000.0f, 2.0f);

    return true;
}

void Program::term()
{
    delete mp_Camera;
    delete mp_ShaderManager;
}

bool Program::load()
{
    LogInfo(getClassName(), "Loading Resources");

    ArrayList<Shader> flatShaderList;
    flatShaderList.add(Shader("Shaders/flat.fs.glsl", GL_FRAGMENT_SHADER));
    flatShaderList.add(Shader("Shaders/flat.vs.glsl", GL_VERTEX_SHADER));
    getShaderManager()->loadProgram("flat", flatShaderList);





    const GLuint ATTR_VERTEX         = 0;

	ArrayList<vec3> verts;
	verts.add(vec3(0.0f, 0.0f, 0.0f)); verts.add(vec3(1.0f, 1.0f, 0.0f)); verts.add(vec3(1.0f, 0.0f, 0.0f));
	verts.add(vec3(0.0f, 0.0f, 0.0f)); verts.add(vec3(0.0f, 1.0f, 0.0f)); verts.add(vec3(1.0f, 1.0f, 0.0f));
	verts.add(vec3(0.0f, 0.0f, 0.0f)); verts.add(vec3(0.0f, 1.0f, 1.0f)); verts.add(vec3(0.0f, 1.0f, 0.0f));
	verts.add(vec3(0.0f, 0.0f, 0.0f)); verts.add(vec3(0.0f, 0.0f, 1.0f)); verts.add(vec3(0.0f, 1.0f, 1.0f));
	verts.add(vec3(0.0f, 1.0f, 0.0f)); verts.add(vec3(1.0f, 1.0f, 1.0f)); verts.add(vec3(1.0f, 1.0f, 0.0f));
	verts.add(vec3(0.0f, 1.0f, 0.0f)); verts.add(vec3(0.0f, 1.0f, 1.0f)); verts.add(vec3(1.0f, 1.0f, 1.0f));
	verts.add(vec3(1.0f, 0.0f, 0.0f)); verts.add(vec3(1.0f, 1.0f, 0.0f)); verts.add(vec3(1.0f, 1.0f, 1.0f));
	verts.add(vec3(1.0f, 0.0f, 0.0f)); verts.add(vec3(1.0f, 1.0f, 1.0f)); verts.add(vec3(1.0f, 0.0f, 1.0f));
	verts.add(vec3(0.0f, 0.0f, 0.0f)); verts.add(vec3(1.0f, 0.0f, 0.0f)); verts.add(vec3(1.0f, 0.0f, 1.0f));
	verts.add(vec3(0.0f, 0.0f, 0.0f)); verts.add(vec3(1.0f, 0.0f, 1.0f)); verts.add(vec3(0.0f, 0.0f, 1.0f));
	verts.add(vec3(0.0f, 0.0f, 1.0f)); verts.add(vec3(1.0f, 0.0f, 1.0f)); verts.add(vec3(1.0f, 1.0f, 1.0f));
	verts.add(vec3(0.0f, 0.0f, 1.0f)); verts.add(vec3(1.0f, 1.0f, 1.0f)); verts.add(vec3(0.0f, 1.0f, 1.0f));

    GLfloat* pVerts = (GLfloat*)&verts[0];

	m_NumVerts = verts.getSize();

	GLuint m_VertBuffer = 0;
	m_VertArray = 0;

	glGenVertexArrays(1, &m_VertArray);
	glBindVertexArray(m_VertArray);

	if (m_VertBuffer == 0)
	{
		glGenBuffers(1, &m_VertBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * m_NumVerts, pVerts, GL_DYNAMIC_DRAW);
	}
	else
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VertBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 3 * m_NumVerts, pVerts);
	}


	if (m_VertBuffer != 0)
	{
		glEnableVertexAttribArray(ATTR_VERTEX);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertBuffer);
		glVertexAttribPointer(ATTR_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}




    return true;
}

void Program::update(const TimeInfo& timeInfo)
{
}

void Program::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glClearDepth(1.0f);

	mat4x4 mView = mp_Camera->getViewMatrix();
	mat4x4 mProj = mp_Camera->getProjectionMatrix();
	mat4x4 mViewProj = mProj * mView;

	mp_ShaderManager->useProgram("flat");

	glm::mat4x4 mModel = mat4(1.0f);
	glm::mat4x4 mModelView, mModelViewProj;

	glm::vec3 m_Pos = vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 m_Scale = vec3(1.0f);
	glm::vec3 m_Rot = vec3(0.0f);

	mModel = glm::translate(mModel, m_Pos);
	mModel = glm::scale(mModel, m_Scale);

	mModel = glm::rotate(mModel, m_Rot.x, vec3(1.0f, 0.0f, 0.0f));
	mModel = glm::rotate(mModel, m_Rot.y, vec3(0.0f, 1.0f, 0.0f));
	mModel = glm::rotate(mModel, m_Rot.z, vec3(0.0f, 0.0f, 1.0f));

	mModelViewProj = mViewProj * mModel;

	GLint m4ModelViewProjLoc  = mp_ShaderManager->getUniformLocation("uModelViewProj");
	GLint v4FlatColorLoc  = mp_ShaderManager->getUniformLocation("uFlatColor");

	mp_ShaderManager->setUniformMatrix4fv(m4ModelViewProjLoc, 1, &mModelViewProj);
	mp_ShaderManager->setUniform4f(v4FlatColorLoc, vec4(0.0f, 0.0f, 1.0f, 1.0f));

	glBindVertexArray(m_VertArray);

	glDrawArrays(GL_TRIANGLES, 0, m_NumVerts);

	glBindVertexArray(0);
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
    m_Width = 1280, m_Height = 768;
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
	GLenum ret = glewInit();
	if (ret != GLEW_OK)
	{
		LogErrorFmt(getClassName(), "Failed to initialize GLEW (Error #%d, %s)", ret, glewGetErrorString(ret));
		return false;
	}

	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

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
	m_Width = width;
	m_Height = height;

	glViewport(0, 0, m_Width, m_Height);

	mp_Camera->resize((float)width, (float)height);
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
