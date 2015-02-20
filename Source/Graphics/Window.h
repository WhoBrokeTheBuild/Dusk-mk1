#ifndef DUSK_WINDOW_H
#define DUSK_WINDOW_H

#include <Arc/ManagedObject.h>
#include <Events/IEventDispatcher.h>
#include <Graphics/Graphics.h>
#include <Scripting/Scripting.h>

#include <Arc/Map.h>

using Arc::Map;

using namespace Dusk::Events;

namespace Dusk
{

namespace Graphics
{

class GraphicsContext;

class Window :
    public Arc::ManagedObject,
    public IEventDispatcher
{
public:

    static const EventID    EVT_RESIZE;
    static const EventID    EVT_KEY_UP;
    static const EventID    EVT_KEY_DOWN;
    static const EventID    EVT_MOUSE_UP;
    static const EventID    EVT_MOUSE_DOWN;
    static const EventID    EVT_MOUSE_MOVE;
    static const EventID    EVT_MOUSE_SCROLL;

    inline Window( void ) :
        mp_GLFWWindow(nullptr),
        mp_GraphicsContext(nullptr),
        m_Width(0),
        m_Height(0),
        m_Fullscreen(false),
        m_Error(false)
    { }

    ~Window( void );

    bool init( const unsigned int& width, const unsigned int& height, const string& title, const bool& fullscreen = false );

    virtual inline string getClassName( void ) const { return "Window"; }

    bool resize( const unsigned int& width, const unsigned int& height );

    inline unsigned int getWidth( void ) const { return m_Width; }
    inline void setWidth( const unsigned int& width ) { resize(width, m_Height); }

    inline unsigned int getHeight( void ) const { return m_Height; }
    inline void setHeight( const unsigned int& height ) { resize(m_Width, height); }

    inline string getTitle( void ) const { return m_Title; }
    void setTitle( const string& title );

    inline bool isFullscreen( void ) const { return m_Fullscreen; }

    bool shouldClose( void );

    GraphicsContext* getGraphicsContext( void );

    void hookResize( const int& width, const int& height );
    void hookKeyUp( const int& key );
    void hookKeyDown( const int& key );
    void hookMouseUp( const int& button );
    void hookMouseDown( const int& button );
    void hookMouseMove( const double& x, const double& y );
    void hookMouseScroll( const double& x, const double& y );

	static void InitScripting( void );
	static int Script_GetWidth( lua_State* pState );
	static int Script_GetHeight( lua_State* pState );
	static int Script_SetWidth( lua_State* pState );
	static int Script_SetHeight( lua_State* pState );
	static int Script_GetTitle( lua_State* pState );
	static int Script_SetTitle( lua_State* pState );

private:

    GLFWwindow*         mp_GLFWWindow;

    GraphicsContext*    mp_GraphicsContext;

    unsigned int        m_Width,
                        m_Height;

    string              m_Title;

    bool                m_Fullscreen;

    bool                m_Error;

}; // class Window

class WindowResizeEventData :
    public EventData
{
public:

    inline WindowResizeEventData( const unsigned int& width, const unsigned int& height, const int& deltaWidth, const int& deltaHeight ) :
        m_Width(width),
        m_Height(height),
        m_DeltaWidth(deltaWidth),
        m_DeltaHeight(deltaHeight)
    { }

    inline WindowResizeEventData( WindowResizeEventData& rhs ) :
        m_Width(rhs.m_Width),
        m_Height(rhs.m_Height),
        m_DeltaWidth(rhs.m_DeltaWidth),
        m_DeltaHeight(rhs.m_DeltaHeight)
    { }

    virtual EventData* clone( void ) const { return New WindowResizeEventData(m_Width, m_Height, m_DeltaWidth, m_DeltaHeight); };

    virtual inline unsigned int getWidth( void ) const { return m_Width; }
    virtual inline unsigned int getHeight( void ) const { return m_Height; }

    virtual inline int getDeltaWidth( void ) const { return m_DeltaWidth; }
    virtual inline int getDeltaHeight( void ) const { return m_DeltaHeight; }

private:

    unsigned int    m_Width,
                    m_Height;

    int             m_DeltaWidth,
                    m_DeltaHeight;

}; // WindowResizeEventData

class WindowKeyEventData :
    public EventData
{
public:

    inline WindowKeyEventData( const unsigned int& key ) :
        m_Key(key)
    { }

    inline WindowKeyEventData( WindowKeyEventData& rhs ) :
        m_Key(rhs.m_Key)
    { }

    virtual EventData* clone( void ) const { return New WindowKeyEventData(m_Key); };

    virtual inline unsigned int getKey( void ) const { return m_Key; }

private:

    unsigned int    m_Key;

}; // WindowKeyEventData

class WindowMouseEventData :
    public EventData
{
public:

    inline WindowMouseEventData( const unsigned int& mouseButton ) :
        m_MouseButton(mouseButton)
    { }

    inline WindowMouseEventData( WindowMouseEventData& rhs ) :
        m_MouseButton(rhs.m_MouseButton)
    { }

    virtual EventData* clone( void ) const { return New WindowMouseEventData(m_MouseButton); };

    virtual inline unsigned int getMouseButton( void ) const { return m_MouseButton; }

private:

    unsigned int    m_MouseButton;

}; // WindowMouseEventData

class WindowMouseMoveEventData :
    public EventData
{
public:

    inline WindowMouseMoveEventData( const int& x, const int& y, const int& dx, const int& dy ) :
        m_X(x),
        m_Y(y),
        m_DeltaX(dx),
        m_DeltaY(dy)
    { }

    inline WindowMouseMoveEventData( WindowMouseMoveEventData& rhs ) :
        m_X(rhs.m_X),
        m_Y(rhs.m_Y),
        m_DeltaX(rhs.m_DeltaX),
        m_DeltaY(rhs.m_DeltaY)
    { }

    virtual EventData* clone( void ) const { return New WindowMouseMoveEventData(m_X, m_Y, m_DeltaX, m_DeltaY); };

    virtual inline int getX( void ) const { return m_X; }
    virtual inline int getY( void ) const { return m_Y; }
    virtual inline int getDeltaX( void ) const { return m_DeltaX; }
    virtual inline int getDeltaY( void ) const { return m_DeltaY; }

private:

    int     m_X,
            m_Y,
            m_DeltaX,
            m_DeltaY;

}; // WindowMouseEventData

class WindowMouseScrollEventData :
    public EventData
{
}; // WindowMouseEventData

extern Map<GLFWwindow*, Dusk::Graphics::Window*> g_Windows;

void glfwError( int error, const char* description );
void glfwResize( GLFWwindow* pGLFWWindow, int width, int height );
void glfwKey( GLFWwindow* pGLFWWindow, int key, int scancode, int action, int mods );
void glfwMouseMove( GLFWwindow* pGLFWWindow, double x, double y );
void glfwMouse( GLFWwindow* pGLFWWindow, int button, int action, int mods );
void glfwMouseScroll( GLFWwindow* pGLFWWindow, double x, double y );

} // namespace Graphics

} // namespace Dusk

#endif // DUSK_WINDOW_H
