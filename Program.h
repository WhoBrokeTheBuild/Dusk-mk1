#ifndef DUSK_PROGRAM_H
#define DUSK_PROGRAM_H

#include "OpenGL.h"

#include "Functions.h"
#include "TimeInfo.h"
#include "ShaderManager.h"

class Program
{

public:

    static inline Program& getInstance()
    {
        static Program prog;

        return prog;
    }

    virtual ~Program();

    void start();
    void update(const TimeInfo& timeInfo);
    void render();

    GLFWwindow* getWindow() { return mp_Window; }

    int getWindowWidth() { return m_Width; }
    int getWindowHeight() { return m_Height; }

    void hookResize( const int& width, const int& height );
    void hookKeyUp( const int& key );
    void hookKeyDown( const int& key );
    void hookMouseUp( const int& button );
    void hookMouseDown( const int& button );
    void hookMouseMove( const double& x, const double& y );
    void hookMouseScroll( const double& x, const double& y );

private:

    Program() {};
    Program(Program const&);
    void operator=(Program const&);

    bool initWindow();

    ShaderManager*      mp_ShaderManager;
    //ResourceManager*    mp_ResourceManager;

    GLFWwindow*         mp_Window;
    int                 m_Width;
    int                 m_Height;

};

void glfwError( int error, const char* description );
void glfwResize( GLFWwindow* window, int width, int height );
void glfwKey( GLFWwindow* window, int key, int scancode, int action, int mods );
void glfwMouseMove( GLFWwindow* window, double x, double y );
void glfwMouse( GLFWwindow* window, int button, int action, int mods );
void glfwMouseScroll( GLFWwindow* window, double x, double y );

#endif // DUSK_PROGRAM_H
