#ifndef DUSK_PROGRAM_H
#define DUSK_PROGRAM_H

#include <Arc/ManagedObject.h>
#include <Graphics/Graphics.h>

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

using namespace Dusk::Graphics;
using namespace Dusk::Scripting;
using namespace Dusk::Timing;
using namespace Dusk::World;

class Program :
    public Arc::ManagedObject
{

public:

    static inline Program& Inst()
    {
        static Program prog;

        return prog;
    }

    virtual inline ~Program() { }

    virtual inline string getClassName( void ) const { return "Program"; }

    void start();
    void update(const TimeInfo& timeInfo);
    void render();

    GraphicsSystem* getGraphicsSystem( void );
	ScriptingSystem* getScriptingSystem( void );
    Camera* getCamera( void );

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

    float               m_TargetFPS;
    float               m_CurrentFPS;


    // Temporary
    Skybox* mp_Skybox;
    Model* mp_Cube;
    float rotation;

}; // class Program

} // namespace Dusk

#endif // DUSK_PROGRAM_H
