#include "Program.h"

#include <Logging/Log.h>
#include <Graphics/Window.h>
#include <Graphics/GraphicsSystem.h>
#include <Graphics/ShaderManager.h>
#include <Graphics/GraphicsContext.h>
#include <Graphics/Model.h>
#include <World/Camera.h>
#include <World/Skybox.h>
#include <Timing/TimeInfo.h>

using namespace Dusk::Logging;
using namespace Dusk::Timing;

Dusk::Graphics::GraphicsSystem* Dusk::Program::getGraphicsSystem( void )
{
    return mp_GraphicsSystem;
}

Dusk::World::Camera* Dusk::Program::getCamera( void )
{
    return mp_Camera;
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

	TimeInfo timeInfo;
    m_TargetFPS = 60.0f;
    const double updateInterval = 1.0f / m_TargetFPS;
    unsigned long long frameCount = 0;

    double timeStart = glfwGetTime();
    double lastTime = timeStart;
	while ( ! getGraphicsSystem()->getWindow()->shouldClose() )
	{
		double time = glfwGetTime();
		double elapsedTime = time - lastTime;
		lastTime = time;

        timeInfo.ElapsedSeconds = elapsedTime;
        timeInfo.ElapsedMilliseconds = timeInfo.ElapsedSeconds * 1000.0f;
        timeInfo.TotalSeconds += elapsedTime;
        timeInfo.TotalMilliseconds += timeInfo.ElapsedMilliseconds;

        timeInfo.Delta = elapsedTime / updateInterval;
        m_CurrentFPS = (float)((updateInterval / elapsedTime) * m_TargetFPS);

        update(timeInfo);
        render();
        getGraphicsSystem()->getGraphicsContext()->swapBuffers();

        ++frameCount;

		glfwPollEvents();
	}

	term();
}

bool Dusk::Program::init()
{
    LogInfo(getClassName(), "Initializing");

    mp_GraphicsSystem = New GraphicsSystem();
    if ( ! mp_GraphicsSystem->init(1024, 768, "Dusk Test", false) )
    {
        LogError(getClassName(), "Failed to initialize Graphics System");
        return false;
    }

    mp_Camera = New Camera((float)getGraphicsSystem()->getWindow()->getWidth(), (float)getGraphicsSystem()->getWindow()->getHeight(),
                           vec3(20.0f), vec3(-1.0f), vec3(0.0f, 1.0f, 0.0f), 45.0f, 0.1f, 10000.0f);

    return true;
}

void Dusk::Program::term()
{
    delete mp_Cube;
    delete mp_Skybox;

    delete mp_Camera;
    mp_Camera = nullptr;

    delete mp_GraphicsSystem;
    mp_GraphicsSystem = nullptr;
}

bool Dusk::Program::load()
{
    LogInfo(getClassName(), "Loading Resources");

    ArrayList<ShaderInfo> flatShaders;
    flatShaders.add(ShaderInfo(GL_FRAGMENT_SHADER, "Assets/Shaders/flat.fs.glsl"));
    flatShaders.add(ShaderInfo(GL_VERTEX_SHADER, "Assets/Shaders/flat.vs.glsl"));
    getGraphicsSystem()->getShaderManager()->loadProgram("flat", flatShaders);

    ArrayList<ShaderInfo> skyboxShaders;
    skyboxShaders.add(ShaderInfo(GL_FRAGMENT_SHADER, "Assets/Shaders/skybox.fs.glsl"));
    skyboxShaders.add(ShaderInfo(GL_VERTEX_SHADER, "Assets/Shaders/skybox.vs.glsl"));
    getGraphicsSystem()->getShaderManager()->loadProgram("skybox", skyboxShaders);

    ArrayList<ShaderInfo> entityShaders;
    entityShaders.add(ShaderInfo(GL_FRAGMENT_SHADER, "Assets/Shaders/entity.fs.glsl"));
    entityShaders.add(ShaderInfo(GL_VERTEX_SHADER, "Assets/Shaders/entity.vs.glsl"));
    getGraphicsSystem()->getShaderManager()->loadProgram("entity", entityShaders);

    rotation = 0.0f;

    mp_Cube = New Model();
    mp_Cube->load("Assets/Models/behemoth/mdl_behemoth.dskm");

    mp_Skybox = New Skybox();
    mp_Skybox->load("Assets/Skyboxes/tex_skybox_space.dskt");

    return true;
}

void Dusk::Program::update(const TimeInfo& timeInfo)
{
    rotation += 0.01f * timeInfo.Delta;
}

void Dusk::Program::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glClearDepth(1.0f);

    mp_Skybox->render();

    ShaderManager* pShaderManager = Program::getInstance().getGraphicsSystem()->getShaderManager();

	mat4x4 mView = mp_Camera->getViewMatrix();
	mat4x4 mProj = mp_Camera->getProjectionMatrix();
	mat4x4 mViewProj = mProj * mView;

	getGraphicsSystem()->getShaderManager()->useProgram("entity");

	glm::mat4x4 mModel = mat4(1.0f);
	glm::mat4x4 mModelView, mModelViewProj;

	glm::vec3 m_Pos = vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 m_Scale = vec3(1.0f);
	glm::vec3 m_Rot = vec3(0.0f, rotation, 0.0f);

	mModel = glm::translate(mModel, m_Pos);
	mModel = glm::scale(mModel, m_Scale);

	mModel = glm::translate(mModel, vec3(0.5f, 0.0f, 0.5f));

	mModel = glm::rotate(mModel, m_Rot.x, vec3(1.0f, 0.0f, 0.0f));
	mModel = glm::rotate(mModel, m_Rot.y, vec3(0.0f, 1.0f, 0.0f));
	mModel = glm::rotate(mModel, m_Rot.z, vec3(0.0f, 0.0f, 1.0f));

	mModel = glm::translate(mModel, vec3(-0.5f, 0.0f, -0.5f));

    mModelView = mView * mModel;
	mModelViewProj = mViewProj * mModel;

	static GLint m4ModelViewLoc      = pShaderManager->getUniformLocation("uModelView");
	static GLint m4ModelViewProjLoc  = pShaderManager->getUniformLocation("uModelViewProj");
	static GLint v3GlobalAmbientLoc  = pShaderManager->getUniformLocation("uGlobalAmbient");
	static GLint v3LightColorLoc     = pShaderManager->getUniformLocation("uLightColor");
	static GLint v3LightDirectionLoc = pShaderManager->getUniformLocation("uLightDirection");

	pShaderManager->setUniformMatrix4fv(m4ModelViewProjLoc, 1, &mModelViewProj);
	pShaderManager->setUniformMatrix4fv(m4ModelViewLoc,     1, &mModelView);

	pShaderManager->setUniform3f(v3GlobalAmbientLoc,  vec3(1.0f));
	pShaderManager->setUniform3f(v3LightColorLoc,     vec3(1.0f));
	pShaderManager->setUniform3f(v3LightDirectionLoc, vec3(-1.0f));

    mp_Cube->render();
}
