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
    Camera* getCamera( void );


	static int Script_GetCamera( lua_State* pState );

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


    // Temporary
    Skybox* mp_Skybox;
    Model* mp_Cube;
    float rotation;

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
