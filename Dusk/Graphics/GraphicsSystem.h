#ifndef DUSK_GRAPHICS_SYSTEM_H
#define DUSK_GRAPHICS_SYSTEM_H

#include <Arc/ManagedObject.h>
#include <Events/IEventDispatcher.h>
#include <Graphics/Graphics.h>
#include <Scripting/Scripting.h>

using namespace Dusk::Events;

namespace Dusk
{

namespace Graphics
{

class Window;
class GraphicsContext;
class ShaderManager;

class GraphicsSystem :
    public Arc::ManagedObject,
    public IEventDispatcher
{
public:

    static const EventID    EVT_RESET;

    inline GraphicsSystem( void ) :
        mp_Window(nullptr),
        mp_ShaderManager(nullptr)
    { }

    virtual ~GraphicsSystem( void );

    virtual inline string getClassName( void ) const { return "Graphics"; }

    bool init( const unsigned int& width, const unsigned int& height, const string& title, const bool& fullscreen = false, const bool& vsync = false );

    Window* getWindow( void );
    GraphicsContext* getGraphicsContext( void );
    ShaderManager* getShaderManager( void );

    inline int getMonitorWidth( void ) const { return m_MonitorWidth; }
    inline int getMonitorHeight( void ) const { return m_MonitorHeight; }
    inline int getMonitorX( void ) const { return m_MonitorX; }
    inline int getMonitorY( void ) const { return m_MonitorY; }

    inline void setVsync( const bool& vsync ) { m_Vsync = vsync; glfwSwapInterval( ( m_Vsync ? 1 : 0) ); }

    void handleReset( const Event& event );

	static void InitScripting( void );
	static int Script_GetWindow( lua_State* pState );
	static int Script_GetGraphicsContext( lua_State* pState );
	static int Script_GetShaderManager( lua_State* pState );

private:

    bool initGL( void );

    Window*             mp_Window;
    ShaderManager*      mp_ShaderManager;

    int                 m_MonitorWidth,
                        m_MonitorHeight,
                        m_MonitorX,
                        m_MonitorY;

    bool                m_Vsync;

}; // class GraphicsSystem

void glfwError( int error, const char* description );

} // namespace Graphics

} // namespace Dusk

#endif // DUSK_GRAPHICS_SYSTEM_H
