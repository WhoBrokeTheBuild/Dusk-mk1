#ifndef DUSK_GRAPHICS_SYSTEM_H
#define DUSK_GRAPHICS_SYSTEM_H

#include <Arc/ManagedObject.h>
#include <Graphics/Graphics.h>
#include <Scripting/Scripting.h>

namespace Dusk
{

namespace Graphics
{

class Window;
class GraphicsContext;
class ShaderManager;

class GraphicsSystem :
    public Arc::ManagedObject
{
public:

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

    inline void setVsync( const bool& vsync ) { glfwSwapInterval( ( vsync ? 1 : 0) ); }

	static void InitScripting( void );
	static int Script_GetWindow( lua_State* pState );
	static int Script_GetGraphicsContext( lua_State* pState );
	static int Script_GetShaderManager( lua_State* pState );

private:

    Window*             mp_Window;
    ShaderManager*      mp_ShaderManager;

}; // class GraphicsSystem

} // namespace Graphics

} // namespace Dusk

#endif // DUSK_GRAPHICS_SYSTEM_H
