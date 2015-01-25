#ifndef DUSK_PROGRAM_H
#define DUSK_PROGRAM_H

#include <Arc/ManagedObject.h>
#include <Graphics/Graphics.h>

namespace Dusk
{

namespace Graphics
{
    class GraphicsSystem;
}

namespace World
{
    class Camera;
}

namespace Timing
{
    class TimeInfo;
}

using namespace Dusk::Graphics;
using namespace Dusk::Timing;
using namespace Dusk::World;

class Program :
    public Arc::ManagedObject
{

public:

    static inline Program& getInstance()
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

private:

    Program() {};
    Program(Program const&);
    void operator=(Program const&);

    bool init();
    void term();
    bool load();

    GraphicsSystem*     mp_Graphics;
    Camera*             mp_Camera;



    // Temporary
    int m_NumVerts;
    GLuint m_VertArray;

}; // class Program

} // namespace Dusk

#endif // DUSK_PROGRAM_H
