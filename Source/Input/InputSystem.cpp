#include "InputSystem.h"

#include <Program.h>
#include <Logging/Log.h>
#include <Graphics/GraphicsSystem.h>
#include <Graphics/Window.h>

using namespace Dusk::Logging;

Dusk::Input::InputSystem::InputSystem( void )
{
    Window* pWindow = Program::Inst()->getGraphicsSystem()->getWindow();
    pWindow->addEventListener(Window::EVT_KEY_UP,       this, &InputSystem::handleKeyUp);
    pWindow->addEventListener(Window::EVT_KEY_DOWN,     this, &InputSystem::handleKeyDown);
    pWindow->addEventListener(Window::EVT_MOUSE_UP,     this, &InputSystem::handleMouseUp);
    pWindow->addEventListener(Window::EVT_MOUSE_DOWN,   this, &InputSystem::handleMouseDown);
    pWindow->addEventListener(Window::EVT_MOUSE_MOVE,   this, &InputSystem::handleMouseMove);
    pWindow->addEventListener(Window::EVT_MOUSE_SCROLL, this, &InputSystem::handleMouseScroll);
}

void Dusk::Input::InputSystem::handleKeyUp(const Event& event)
{
    WindowKeyEventData* pData = event.getDataAs<WindowKeyEventData>();
    //LogInfoFmt(getClassName(), "Key Up: %d", pData->getKey());
}

void Dusk::Input::InputSystem::handleKeyDown(const Event& event)
{
    WindowKeyEventData* pData = event.getDataAs<WindowKeyEventData>();
    //LogInfoFmt(getClassName(), "Key Down: %d", pData->getKey());
}

void Dusk::Input::InputSystem::handleMouseUp(const Event& event)
{
    WindowMouseEventData* pData = event.getDataAs<WindowMouseEventData>();
    //LogInfoFmt(getClassName(), "Mouse Up: %d", pData->getMouseButton());
}

void Dusk::Input::InputSystem::handleMouseDown(const Event& event)
{
    WindowMouseEventData* pData = event.getDataAs<WindowMouseEventData>();
    //LogInfoFmt(getClassName(), "Mouse Down: %d", pData->getMouseButton());
}

void Dusk::Input::InputSystem::handleMouseMove(const Event& event)
{
    WindowMouseMoveEventData* pData = event.getDataAs<WindowMouseMoveEventData>();
    //LogInfoFmt(getClassName(), "Mouse Move: %d, %d", pData->getX(), pData->getY());
}

void Dusk::Input::InputSystem::handleMouseScroll(const Event& event)
{
    WindowMouseScrollEventData* pData = event.getDataAs<WindowMouseScrollEventData>();
}
