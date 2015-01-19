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
    mp_Camera = New Camera((float)m_Width, (float)m_Height, vec3(20.0f, 150.0f, 20.0f), vec3(0.7f, 0.0f, 0.7f), vec3(0.0f, 1.0f, 0.0f), 45.0f, 0.1f, 10000.0f, 2.0f);

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

	LogInfoFmt(getClassName(), "View Matrix:\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n",
        mView[0][0], mView[0][1], mView[0][2], mView[0][3],
        mView[1][0], mView[1][1], mView[1][2], mView[1][3],
        mView[2][0], mView[2][1], mView[2][2], mView[2][3],
        mView[3][0], mView[3][1], mView[3][2], mView[3][3]);

	LogInfoFmt(getClassName(), "Projection Matrix:\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n",
        mProj[0][0], mProj[0][1], mProj[0][2], mProj[0][3],
        mProj[1][0], mProj[1][1], mProj[1][2], mProj[1][3],
        mProj[2][0], mProj[2][1], mProj[2][2], mProj[2][3],
        mProj[3][0], mProj[3][1], mProj[3][2], mProj[3][3]);

	LogInfoFmt(getClassName(), "View/Projection Matrix:\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n",
        mViewProj[0][0], mViewProj[0][1], mViewProj[0][2], mViewProj[0][3],
        mViewProj[1][0], mViewProj[1][1], mViewProj[1][2], mViewProj[1][3],
        mViewProj[2][0], mViewProj[2][1], mViewProj[2][2], mViewProj[2][3],
        mViewProj[3][0], mViewProj[3][1], mViewProj[3][2], mViewProj[3][3]);

	mp_ShaderManager->useProgram("flat");

	glm::mat4x4 mModel = mat4(1.0f);
	glm::mat4x4 mModelView, mModelViewProj;

	glm::vec3 m_Pos = vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 m_Scale = vec3(10.0f);
	glm::vec3 m_Rot = vec3(0.0f);

	mModel = glm::translate(mModel, m_Pos);
	mModel = glm::scale(mModel, m_Scale);

	mModel = glm::rotate(mModel, m_Rot.x, vec3(1.0f, 0.0f, 0.0f));
	mModel = glm::rotate(mModel, m_Rot.y, vec3(0.0f, 1.0f, 0.0f));
	mModel = glm::rotate(mModel, m_Rot.z, vec3(0.0f, 0.0f, 1.0f));

	LogInfoFmt(getClassName(), "Model Matrix:\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n",
        mModel[0][0], mModel[0][1], mModel[0][2], mModel[0][3],
        mModel[1][0], mModel[1][1], mModel[1][2], mModel[1][3],
        mModel[2][0], mModel[2][1], mModel[2][2], mModel[2][3],
        mModel[3][0], mModel[3][1], mModel[3][2], mModel[3][3]);

	mModelViewProj = mViewProj * mModel;

	LogInfoFmt(getClassName(), "Model/View/Projection Matrix:\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n",
        mModelViewProj[0][0], mModelViewProj[0][1], mModelViewProj[0][2], mModelViewProj[0][3],
        mModelViewProj[1][0], mModelViewProj[1][1], mModelViewProj[1][2], mModelViewProj[1][3],
        mModelViewProj[2][0], mModelViewProj[2][1], mModelViewProj[2][2], mModelViewProj[2][3],
        mModelViewProj[3][0], mModelViewProj[3][1], mModelViewProj[3][2], mModelViewProj[3][3]);

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
    m_Width = 800, m_Height = 600;
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

	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);

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
