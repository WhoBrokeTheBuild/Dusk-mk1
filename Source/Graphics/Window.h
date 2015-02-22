#ifndef DUSK_WINDOW_H
#define DUSK_WINDOW_H

#include <Arc/ManagedObject.h>
#include <Events/IEventDispatcher.h>
#include <Graphics/Graphics.h>
#include <Input/Input.h>
#include <Scripting/Scripting.h>

#include <Arc/Map.h>

using Arc::Map;

using namespace Dusk::Events;
using namespace Dusk::Input;

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

    inline int getX( void ) { int x; int y; glfwGetWindowPos(mp_GLFWWindow, &x, &y); return x; }
    inline int getY( void ) { int x; int y; glfwGetWindowPos(mp_GLFWWindow, &x, &y); return y; }

    inline int setX( const int& x ) { glfwSetWindowPos(mp_GLFWWindow, x, getY()); }
    inline int setY( const int& y ) { glfwSetWindowPos(mp_GLFWWindow, getX(), y); }
    inline int setPos( const int& x, const int& y ) { glfwSetWindowPos(mp_GLFWWindow, x, y); }

    inline string getTitle( void ) const { return m_Title; }
    void setTitle( const string& title );

    inline bool isFullscreen( void ) const { return m_Fullscreen; }
    inline void setFullscreen( const bool& fullscreen ) { m_Fullscreen = true; }

    inline bool isDecorated( void ) const { return m_Decorated; }
    inline bool setDecorated( const bool& decorated ) { m_Decorated = decorated; }

    bool shouldClose( void );

    GraphicsContext* getGraphicsContext( void );

    void hookResize( const int& width, const int& height );

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

    bool                m_Fullscreen,
                        m_Decorated;

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

void glfwError( int error, const char* description );
void glfwResize( GLFWwindow* pGLFWWindow, int width, int height );

} // namespace Graphics

} // namespace Dusk

#endif // DUSK_WINDOW_H
