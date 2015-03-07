#ifndef DUSK_PROGRAM_H
#define DUSK_PROGRAM_H

#include <Arc/ManagedObject.h>
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

class Program :
    public Arc::ManagedObject,
    public IEventDispatcher
{

public:

    static const EventID  EVT_UPDATE;
    static const EventID  EVT_RENDER;

    static inline Program* Inst()
    {
        static Program* pProgram = New Program();

        return pProgram;
    }

    virtual inline ~Program() { }

    virtual inline string getClassName( void ) const { return "Program"; }

    void run();
    void update(TimeInfo& timeInfo);
    void render();

    GraphicsSystem* getGraphicsSystem( void );
	ScriptingSystem* getScriptingSystem( void );
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

    bool init();
    void term();
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
