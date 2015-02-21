#ifndef DUSK_INPUT_SYSTEM_H
#define DUSK_INPUT_SYSTEM_H

#include <Arc/ManagedObject.h>
#include <Events/IEventDispatcher.h>
#include <Input/Input.h>
#include <Input/Key.h>
#include <Input/MouseButton.h>

using namespace Dusk::Events;

namespace Dusk
{

namespace Input
{

class InputSystem :
    public Arc::ManagedObject,
    public IEventDispatcher
{
public:

    static const EventID    EVT_KEY_UP;
    static const EventID    EVT_KEY_DOWN;
    static const EventID    EVT_MOUSE_UP;
    static const EventID    EVT_MOUSE_DOWN;
    static const EventID    EVT_MOUSE_MOVE;
    static const EventID    EVT_MOUSE_SCROLL;

    InputSystem( void );

    virtual inline string getClassName( void ) const { return "Input System"; }

    void hookKeyUp( const GLFWKey& key );
    void hookKeyDown( const GLFWKey& key );
    void hookMouseUp( const GLFWMouseButton& button );
    void hookMouseDown( const GLFWMouseButton& button );
    void hookMouseMove( const double& x, const double& y );
    void hookMouseScroll( const double& x, const double& y );

private:

    int     m_MouseX,
            m_MouseY;

}; // class InputSystem

class KeyEventData :
    public EventData
{
public:

    inline KeyEventData( const Key& key ) :
        m_Key(key)
    { }

    inline KeyEventData( KeyEventData& rhs ) :
        m_Key(rhs.m_Key)
    { }

    virtual EventData* clone( void ) const { return New KeyEventData(m_Key); };

    virtual inline Key getKey( void ) const { return m_Key; }

private:

    Key    m_Key;

}; // KeyEventData

class MouseEventData :
    public EventData
{
public:

    inline MouseEventData( const MouseButton& mouseButton ) :
        m_MouseButton(mouseButton)
    { }

    inline MouseEventData( MouseEventData& rhs ) :
        m_MouseButton(rhs.m_MouseButton)
    { }

    virtual EventData* clone( void ) const { return New MouseEventData(m_MouseButton); };

    virtual inline GLFWMouseButton getMouseButton( void ) const { return m_MouseButton; }

private:

    MouseButton    m_MouseButton;

}; // MouseEventData

class MouseMoveEventData :
    public EventData
{
public:

    inline MouseMoveEventData( const int& x, const int& y, const int& dx, const int& dy ) :
        m_X(x),
        m_Y(y),
        m_DeltaX(dx),
        m_DeltaY(dy)
    { }

    inline MouseMoveEventData( MouseMoveEventData& rhs ) :
        m_X(rhs.m_X),
        m_Y(rhs.m_Y),
        m_DeltaX(rhs.m_DeltaX),
        m_DeltaY(rhs.m_DeltaY)
    { }

    virtual EventData* clone( void ) const { return New MouseMoveEventData(m_X, m_Y, m_DeltaX, m_DeltaY); };

    virtual inline int getX( void ) const { return m_X; }
    virtual inline int getY( void ) const { return m_Y; }
    virtual inline int getDeltaX( void ) const { return m_DeltaX; }
    virtual inline int getDeltaY( void ) const { return m_DeltaY; }

private:

    float   m_X,
            m_Y,
            m_DeltaX,
            m_DeltaY;

}; // MouseMoveEventData

void glfwKey( GLFWwindow* pGLFWWindow, int key, int scancode, int action, int mods );
void glfwMouseMove( GLFWwindow* pGLFWWindow, double x, double y );
void glfwMouse( GLFWwindow* pGLFWWindow, int button, int action, int mods );
void glfwMouseScroll( GLFWwindow* pGLFWWindow, double x, double y );

} // namespace Input

} // namespace Dusk

#endif // DUSK_INPUT_SYSTEM_H
