#ifndef DUSK_MOUSE_BUTTON_H
#define DUSK_MOUSE_BUTTON_H

#include <Graphics/Graphics.h>

namespace Dusk
{

namespace Input
{

enum MouseButton
{
    INVALID_MOUSE_BUTTON    = -1,

    MOUSE_BUTTON_LEFT       = 1,
    MOUSE_BUTTON_RIGHT      = 2,
    MOUSE_BUTTON_MIDDLE     = 3

}; // enum MouseButton

inline MouseButton GLFW2DuskMouseButton( const GLFWMouseButton& glfwMouseButton )
{
    if (glfwMouseButton == GLFW_MOUSE_BUTTON_LEFT)
        return MOUSE_BUTTON_LEFT;
    else if (glfwMouseButton == GLFW_MOUSE_BUTTON_RIGHT)
        return MOUSE_BUTTON_RIGHT;
    else if (glfwMouseButton == GLFW_MOUSE_BUTTON_MIDDLE)
        return MOUSE_BUTTON_MIDDLE;

    return INVALID_MOUSE_BUTTON;
}

} // namespace Input

} // namespace Dusk

#endif // DUSK_MOUSE_BUTTON_H
