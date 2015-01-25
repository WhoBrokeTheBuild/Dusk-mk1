#include "GraphicsContext.h"

#include <Graphics/Window.h>

bool Dusk::Graphics::GraphicsContext::bind(void)
{
    if (mp_GLFWWindow == nullptr)
        return false;

	glfwMakeContextCurrent(mp_GLFWWindow);

	glfwSwapInterval(0);

	return true;
}

void Dusk::Graphics::GraphicsContext::swapBuffers(void)
{
    glfwSwapBuffers(mp_GLFWWindow);
}
