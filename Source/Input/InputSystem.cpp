#include "InputSystem.h"

#include <Program.h>
#include <Logging/Log.h>
#include <Graphics/GraphicsSystem.h>
#include <Graphics/Window.h>

using namespace Dusk::Logging;

const Dusk::Events::EventID Dusk::Input::InputSystem::EVT_KEY_UP         = 1;
const Dusk::Events::EventID Dusk::Input::InputSystem::EVT_KEY_DOWN       = 2;
const Dusk::Events::EventID Dusk::Input::InputSystem::EVT_MOUSE_UP       = 3;
const Dusk::Events::EventID Dusk::Input::InputSystem::EVT_MOUSE_DOWN     = 4;
const Dusk::Events::EventID Dusk::Input::InputSystem::EVT_MOUSE_MOVE     = 5;
const Dusk::Events::EventID Dusk::Input::InputSystem::EVT_MOUSE_SCROLL   = 6;

Dusk::Input::InputSystem::InputSystem( void )
{
}

void Dusk::Input::InputSystem::hookKeyUp( const int& key )
{
    dispatch(Event(InputSystem::EVT_KEY_UP, KeyEventData(GLFW2DuskKey(key))));
}

void Dusk::Input::InputSystem::hookKeyDown( const int& key )
{
    dispatch(Event(InputSystem::EVT_KEY_DOWN, KeyEventData(GLFW2DuskKey(key))));
}

void Dusk::Input::InputSystem::hookMouseUp( const int& button )
{
    dispatch(Event(InputSystem::EVT_MOUSE_UP, MouseEventData(GLFW2DuskMouseButton(button))));
}

void Dusk::Input::InputSystem::hookMouseDown( const int& button )
{
    dispatch(Event(InputSystem::EVT_MOUSE_DOWN, MouseEventData(GLFW2DuskMouseButton(button))));
}

void Dusk::Input::InputSystem::hookMouseMove( const double& x, const double& y )
{
    int deltaX = x - m_MouseX;
    int deltaY = y - m_MouseY;

	m_MouseX = x;
	m_MouseY = y;

    dispatch(Event(InputSystem::EVT_MOUSE_MOVE, MouseMoveEventData(m_MouseX, m_MouseY, deltaX, deltaY)));
}

void Dusk::Input::InputSystem::hookMouseScroll( const double& x, const double& y )
{
    dispatch(Event(InputSystem::EVT_MOUSE_DOWN, MouseScrollEventData((int)x, (int)y)));
}

void Dusk::Input::glfwKey( GLFWwindow* pGLFWWindow, int key, int scancode, int action, int mods )
{
    InputSystem* pInputSystem = Program::Inst()->getInputSystem();

	switch (action)
	{
	case GLFW_PRESS:

        pInputSystem->hookKeyDown(key);

		break;
	case GLFW_RELEASE:

        pInputSystem->hookKeyUp(key);

		break;
	case GLFW_REPEAT:


		break;
	}
}

void Dusk::Input::glfwMouseMove( GLFWwindow* pGLFWWindow, double x, double y )
{
    InputSystem* pInputSystem = Program::Inst()->getInputSystem();
    pInputSystem->hookMouseMove(x, y);
}

void Dusk::Input::glfwMouse( GLFWwindow* pGLFWWindow, int button, int action, int mods )
{
    InputSystem* pInputSystem = Program::Inst()->getInputSystem();

	switch (action)
	{
	case GLFW_PRESS:

        pInputSystem->hookMouseDown(button);

		break;
	case GLFW_RELEASE:

        pInputSystem->hookMouseUp(button);

		break;
	}
}

void Dusk::Input::glfwMouseScroll( GLFWwindow* pGLFWWindow, double x, double y )
{
    InputSystem* pInputSystem = Program::Inst()->getInputSystem();
    pInputSystem->hookMouseScroll(x, y);
}
