#include "Program.h"

#include <Logging/Log.h>
#include <Graphics/Window.h>
#include <Graphics/GraphicsSystem.h>
#include <Graphics/ShaderManager.h>
#include <Graphics/GraphicsContext.h>
#include <Graphics/Model.h>
#include <Scripting/ScriptingSystem.h>
#include <World/Camera.h>
#include <World/Skybox.h>
#include <World/Entity.h>
#include <Input/InputSystem.h>
#include <Timing/TimeInfo.h>

using namespace Dusk::Logging;
using namespace Dusk::Timing;

const Dusk::Events::EventID Dusk::Program::EVT_UPDATE = 1;
const Dusk::Events::EventID Dusk::Program::EVT_RENDER = 2;

Dusk::Graphics::GraphicsSystem* Dusk::Program::getGraphicsSystem( void )
{
    return mp_GraphicsSystem;
}

Dusk::Scripting::ScriptingSystem* Dusk::Program::getScriptingSystem(void)
{
	return mp_ScriptingSystem;
}

Dusk::Input::InputSystem* Dusk::Program::getInputSystem(void)
{
	return mp_InputSystem;
}

Dusk::World::Camera* Dusk::Program::getCamera( void )
{
    return mp_Camera;
}

void Dusk::Program::run()
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
    m_ShouldExit = false;
	while ( ! getGraphicsSystem()->getWindow()->shouldClose() && ! m_ShouldExit )
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

	mp_ScriptingSystem = New ScriptingSystem();
	mp_ScriptingSystem->init();
	Log::InitScripting();

    mp_GraphicsSystem = New GraphicsSystem();
    if ( ! mp_GraphicsSystem->init(640, 480, "Dusk", false) )
    {
        LogError(getClassName(), "Failed to initialize Graphics System");
        return false;
    }
	GraphicsSystem::InitScripting();

    //getGraphicsSystem()->getWindow()->setDecorated(false);
    getGraphicsSystem()->getWindow()->setResizable(false);
    getGraphicsSystem()->getWindow()->reset();

	mp_InputSystem = New InputSystem();

    mp_Camera = New Camera((float)getGraphicsSystem()->getWindow()->getWidth(), (float)getGraphicsSystem()->getWindow()->getHeight(),
                           vec3(2.0f), vec3(-1.0f), vec3(0.0f, 1.0f, 0.0f), 45.0f, 1.0f, 1000.0f);

	mp_ScriptingSystem->runScript("Assets/Scripts/Dusk.lua");
	mp_ScriptingSystem->runScript("Assets/Scripts/Setup.lua");

	mp_InputSystem->addEventListener(InputSystem::EVT_KEY_DOWN,   this, &Program::handleKeyDown);
	mp_InputSystem->addEventListener(InputSystem::EVT_KEY_UP,     this, &Program::handleKeyUp);
	mp_InputSystem->addEventListener(InputSystem::EVT_MOUSE_DOWN, this, &Program::handleMouseDown);
	mp_InputSystem->addEventListener(InputSystem::EVT_MOUSE_UP,   this, &Program::handleMouseUp);
	mp_InputSystem->addEventListener(InputSystem::EVT_MOUSE_MOVE, this, &Program::handleMouseMove);

    //m_MovingWindow = false;
    //m_MouseX = m_MouseY =INT_MAX;
    //m_WindowX = m_WindowY =INT_MAX;
    //m_WindowUpdateTimeoutMax = 20;
    //m_WindowUpdateTimeout = m_WindowUpdateTimeoutMax;

    rotation = 0.0f;
    rotationSpeed = 0.0001f;

    return true;
}

void Dusk::Program::term()
{
    delete mp_Cube;
    delete mp_Skybox;

    delete mp_Camera;
    mp_Camera = nullptr;

    delete mp_InputSystem;
    mp_InputSystem = nullptr;

    delete mp_GraphicsSystem;
    mp_GraphicsSystem = nullptr;

    delete mp_ScriptingSystem;
    mp_ScriptingSystem = nullptr;
}

bool Dusk::Program::load()
{
    LogInfo(getClassName(), "Loading Resources");

	mp_ScriptingSystem->runScript("Assets/Scripts/Resources.lua");

    rotation = 0.0f;

    mp_Cube = New Entity();
    mp_Cube->init();

    Model* pCubeModel = New Model();
    pCubeModel->load("Assets/Models/mdl_cube.dskm");

    mp_Cube->addModel(pCubeModel);

    mp_Skybox = New Skybox();
    mp_Skybox->load("Assets/Skyboxes/tex_skybox_stormydays.dskt");

    return true;
}

void Dusk::Program::update(TimeInfo& timeInfo)
{
    UpdateEventData evtData(&timeInfo);
    dispatch(Event(Program::EVT_UPDATE, evtData));

    mp_Cube->setRot(vec3(0.0f, rotation, 0.0f));
    rotation += rotationSpeed;// * timeInfo.Delta;

    //Window* pWindow = getGraphicsSystem()->getWindow();

    //int x = pWindow->getX();
    //int y = pWindow->getY();

    //if (m_WindowX == INT_MAX)
    //    m_WindowX = x;
    //if (m_WindowY == INT_MAX)
    //    m_WindowY = y;

    //if (m_MovingWindow)
    //{
    //    m_WindowUpdateTimeout -= timeInfo.ElapsedMilliseconds;
    //    if (m_WindowUpdateTimeout <= 0)
    //    {
    //        m_WindowUpdateTimeout = m_WindowUpdateTimeoutMax;

    //        pWindow->setPos(m_WindowX, m_WindowY);
    //    }
    //}
}

void Dusk::Program::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glClearDepth(1.0f);

    mp_Skybox->render();
    glClear(GL_DEPTH_BUFFER_BIT);

	dispatch(Event(Program::EVT_RENDER, RenderEventData()));

    mp_Cube->render();
}

int Dusk::Program::Script_GetCamera( lua_State* pState )
{
    lua_pushinteger(pState, (unsigned long)Program::Inst()->getCamera());

	return 1;
}

void Dusk::Program::handleKeyDown( const Event& event )
{
    const KeyEventData* pData = event.getDataAs<KeyEventData>();
    if (pData->getKey() == KEY_ESCAPE)
        m_ShouldExit = true;
}

void Dusk::Program::handleKeyUp( const Event& event )
{
    //const KeyEventData* pData = event.getDataAs<KeyEventData>();
}

void Dusk::Program::handleMouseDown( const Event& event )
{
    //const MouseEventData* pData = event.getDataAs<MouseEventData>();
    //Window* pWindow = getGraphicsSystem()->getWindow();

    //if (pData->getMouseButton() == MOUSE_BUTTON_LEFT)
    //{
    //    int relY = m_MouseY - m_WindowY;
    //    if (relY >= 0 && relY <= 50)
    //    {
    //        int relX = m_MouseX - m_WindowX;
    //        if (relX >= (int)pWindow->getWidth() - 50)
    //        {
    //            m_ShouldExit = true;
    //        }
    //        else
    //        {
    //            m_MovingWindow = true;
    //        }
    //    }
    //}
}

void Dusk::Program::handleMouseUp( const Event& event )
{
    //const MouseEventData* pData = event.getDataAs<MouseEventData>();

    //if (m_MovingWindow && pData->getMouseButton() == MOUSE_BUTTON_LEFT)
    //    m_MovingWindow = false;
}

void Dusk::Program::handleMouseMove( const Event& event )
{
    //const MouseMoveEventData* pData = event.getDataAs<MouseMoveEventData>();
    //Window* pWindow = getGraphicsSystem()->getWindow();

    //if (m_MouseX == INT_MAX)
    //    m_MouseX = pData->getX();
    //if (m_MouseY == INT_MAX)
    //    m_MouseY = pData->getY();

    //int winX = pWindow->getX();
    //int winY = pWindow->getY();

    //int newMouseX = pData->getX() + winX;
    //int newMouseY = pData->getY() + winY;
    //int dX = newMouseX - m_MouseX;
    //int dY = newMouseY - m_MouseY;
    //m_MouseX = newMouseX;
    //m_MouseY = newMouseY;

    //if (m_MovingWindow)
    //{
    //    if (m_WindowX == INT_MAX)
    //        m_WindowX = winX;
    //    if (m_WindowY == INT_MAX)
    //        m_WindowY = winY;

    //    if (dX != 0)
    //        m_WindowX += dX;
    //    if (dY != 0)
    //        m_WindowY += dY;
    //}
}
