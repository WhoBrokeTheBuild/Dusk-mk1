#ifndef DUSK_WINDOW_H
#define DUSK_WINDOW_H

#include <Arc/ManagedObject.h>
#include <Arc/Map.h>
#include <Graphics/Graphics.h>
#include <Scripting/Scripting.h>

using Arc::Map;

namespace Dusk
{

namespace Graphics
{

class GraphicsContext;

class Window :
    public Arc::ManagedObject
{
public:

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
