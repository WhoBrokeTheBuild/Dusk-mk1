#ifndef DUSK_PROGRAM_H
#define DUSK_PROGRAM_H

#include <Arc/ManagedObject.h>
#include <Dusk.h>
#include <Events/IEventDispatcher.h>
#include <Graphics/Graphics.h>
#include <Scripting/Scripting.h>

namespace Dusk
{

namespace Graphics
{
    class GraphicsSystem;
    class Model;
}

namespace Scripting
{
	class ScriptingSystem;
}

namespace World
{
    class Camera;
    class Skybox;
    class Entity;
}

namespace Timing
{
    class TimeInfo;
}

namespace Input
{
    class InputSystem;
}

using namespace Dusk::Events;
using namespace Dusk::Graphics;
using namespace Dusk::Scripting;
using namespace Dusk::Timing;
using namespace Dusk::World;
using namespace Dusk::Input;

/// The main program that manages all systems as well as the update/render loop.
/**
 * The main program that orchestrates all subsystems and controls the
 * update/render loop. The program class is a singleton and can be accessed via
 * the Program::Inst() static function. All systems can be accessed from the
 * instance via their get* functions such as getGraphicsSystem(). The Program
 * class also dispatches the EVT_UPDATE and EVT_RENDER events which can be
 * hooked into.
 */
class Program :
    public Arc::ManagedObject,
    public IEventDispatcher
{

public:

    /// The Update event ID
    static const EventID  EVT_UPDATE;
    /// The Render event ID
    static const EventID  EVT_RENDER;

    /// Gets the static Program instance, or creates one if none exists.
    /**
     * @return A pointer to the static instance of the Program singleton class.
     */
    static inline Program* Inst()
    {
        static Program* pProgram = New Program();

        return pProgram;
    }

    virtual inline ~Program() { }

    virtual inline string getClassName( void ) const { return "Program"; }

    /// This begins the initialization of systems and the loading of resources.
    /**
     * This function will call the init() and load() functions as well as
     * construct the TimeInfo variable and run the update/render loop until
     * either the program decides to exit or the window's X button was clicked.
     */
    void run();

    /// Access the Graphics::GraphicsSystem pointer
    GraphicsSystem* getGraphicsSystem( void );

    /// Access the Scripting::ScriptingSystem pointer
	ScriptingSystem* getScriptingSystem( void );

    /// Access the Input::InputSystem pointer
	InputSystem* getInputSystem( void );

    Camera* getCamera( void );

	static int Script_GetCamera( lua_State* pState );

	void handleKeyDown( const Event& event );
	void handleKeyUp( const Event& event );
	void handleMouseDown( const Event& event );
	void handleMouseUp( const Event& event );
	void handleMouseMove( const Event& event );

private:

    Program() {};
    Program(Program const&);
    void operator=(Program const&);

    /// Base update function that will call the update event.
    /**
     * Dispatch the update event and pass the TimeInfo variable along.
     * @param timeInfo the current time information from run()
     */
    void update(TimeInfo& timeInfo);

    /// Base render function that will call the render event.
    /**
     * This function will trigger the render event as well as clear
     * previous frame and trigger the swapping of screen buffers.
     */
    void render();

    /// Constructs the subsystems ands runs the initialization scripts.
    /**
     *
     */
    bool init();
    /// Destructs the subsystems and cleans up memory.
    void term();
    /// Loads resources and runs resource loading scripts.
    bool load();

    GraphicsSystem*     mp_GraphicsSystem;
    Camera*             mp_Camera;

	ScriptingSystem*	mp_ScriptingSystem;

	InputSystem*        mp_InputSystem;

    float               m_TargetFPS;
    float               m_CurrentFPS;

    bool                m_ShouldExit;

    bool                m_MovingWindow;
    int                 m_MouseX,
                        m_MouseY,
                        m_WindowX,
                        m_WindowY,
                        m_WindowUpdateTimeout,
                        m_WindowUpdateTimeoutMax;

    // Temporary
    Skybox* mp_Skybox;
    Entity* mp_Cube;
    float rotation;
    float rotationSpeed;

}; // class Program

class UpdateEventData :
    public EventData
{
public:

    inline UpdateEventData( TimeInfo* pTimeInfo ) :
        mp_TimeInfo(pTimeInfo)
    { }

    inline UpdateEventData( UpdateEventData& rhs ) :
        mp_TimeInfo(rhs.mp_TimeInfo)
    { }

    virtual EventData* clone( void ) const { return New UpdateEventData(mp_TimeInfo); };

    virtual inline TimeInfo* getTimeInfo( void ) const { return mp_TimeInfo; }

private:

    TimeInfo*   mp_TimeInfo;

}; // class UpdateEventData

class RenderEventData :
    public EventData
{
}; // class RenderEventData

} // namespace Dusk

#endif // DUSK_PROGRAM_H
