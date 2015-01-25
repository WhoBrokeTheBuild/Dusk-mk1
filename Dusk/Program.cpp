#include "Program.h"

#include <Logging/Log.h>
#include <Graphics/Window.h>
#include <Graphics/GraphicsSystem.h>
#include <Graphics/ShaderManager.h>
#include <Graphics/GraphicsContext.h>
#include <World/Camera.h>
#include <Timing/TimeInfo.h>

using namespace Dusk::Logging;

Dusk::Graphics::GraphicsSystem* Dusk::Program::getGraphicsSystem( void )
{
    return mp_Graphics;
}

void Dusk::Program::start()
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
	while ( ! getGraphicsSystem()->getWindow()->shouldClose() )
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
			getGraphicsSystem()->getGraphicsContext()->swapBuffers();
		}

		glfwPollEvents();
	}

	term();
}

bool Dusk::Program::init()
{
    LogInfo(getClassName(), "Initializing");

    mp_Graphics = New GraphicsSystem();
    if ( ! mp_Graphics->init(640, 480, "Dusk Test", false) )
    {
        LogError(getClassName(), "Failed to initialize Graphics System");
        return false;
    }

    mp_Camera = New Camera((float)getGraphicsSystem()->getWindow()->getWidth(), (float)getGraphicsSystem()->getWindow()->getHeight(),
                           vec3(3.0f, 3.0f, 3.0f), vec3(-1.0f), vec3(0.0f, 1.0f, 0.0f), 45.0f, 0.1f, 10000.0f);

    return true;
}

void Dusk::Program::term()
{
    delete mp_Camera;
    delete mp_Graphics;
}

bool Dusk::Program::load()
{
    LogInfo(getClassName(), "Loading Resources");

    ArrayList<ShaderInfo> shaders;
    shaders.add(ShaderInfo(GL_FRAGMENT_SHADER, "Assets/Shaders/flat.fs.glsl"));
    shaders.add(ShaderInfo(GL_VERTEX_SHADER, "Assets/Shaders/flat.vs.glsl"));
    getGraphicsSystem()->getShaderManager()->loadProgram("flat", shaders);

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

void Dusk::Program::update(const TimeInfo& timeInfo)
{
}

void Dusk::Program::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glClearDepth(1.0f);

	mat4x4 mView = mp_Camera->getViewMatrix();
	mat4x4 mProj = mp_Camera->getProjectionMatrix();
	mat4x4 mViewProj = mProj * mView;

	getGraphicsSystem()->getShaderManager()->useProgram("flat");

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

	GLint m4ModelViewProjLoc  = getGraphicsSystem()->getShaderManager()->getUniformLocation("uModelViewProj");
	GLint v4FlatColorLoc  = getGraphicsSystem()->getShaderManager()->getUniformLocation("uFlatColor");

	getGraphicsSystem()->getShaderManager()->setUniformMatrix4fv(m4ModelViewProjLoc, 1, &mModelViewProj);
	getGraphicsSystem()->getShaderManager()->setUniform4f(v4FlatColorLoc, vec4(0.0f, 0.0f, 1.0f, 1.0f));

	glBindVertexArray(m_VertArray);

	glDrawArrays(GL_TRIANGLES, 0, m_NumVerts);

	glBindVertexArray(0);
}
