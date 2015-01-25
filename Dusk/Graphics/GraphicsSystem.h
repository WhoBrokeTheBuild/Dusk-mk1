#ifndef DUSK_GRAPHICS_SYSTEM_H
#define DUSK_GRAPHICS_SYSTEM_H

#include <Arc/ManagedObject.h>
#include <Graphics/Graphics.h>

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

    bool init( const unsigned int& width, const unsigned int& height, const string& title, const bool& fullscreen = false );

    Window* getWindow( void );
    GraphicsContext* getGraphicsContext( void );
    ShaderManager* getShaderManager( void );

private:

    Window*             mp_Window;
    ShaderManager*      mp_ShaderManager;

}; // class GraphicsSystem

} // namespace Graphics

} // namespace Dusk

#endif // DUSK_GRAPHICS_SYSTEM_H
