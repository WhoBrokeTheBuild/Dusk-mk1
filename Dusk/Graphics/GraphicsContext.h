#ifndef DUSK_GRAPHICS_CONTEXT_H
#define DUSK_GRAPHICS_CONTEXT_H

#include <Arc/ManagedObject.h>
#include <Graphics/Graphics.h>

namespace Dusk
{

namespace Graphics
{

class Window;

class GraphicsContext :
    public Arc::ManagedObject
{

    friend class Window;

public:

    virtual inline string getClassName( void ) const { return "Graphics Context"; }

    bool bind( void );
    void swapBuffers( void );

private:

    inline GraphicsContext( GLFWwindow* pGLFWWindow ) :
        mp_GLFWWindow(pGLFWWindow)
    { }

    GLFWwindow*     mp_GLFWWindow;

}; // GraphicsContext

} // Graphics

} // Dusk

#endif // DUSK_GRAPHICS_CONTEXT_H
