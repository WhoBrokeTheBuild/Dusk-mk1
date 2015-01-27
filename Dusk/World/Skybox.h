#ifndef DUSK_SKYBOX_H
#define DUSK_SKYBOX_H

#include <Arc/ManagedObject.h>

namespace Dusk
{

namespace Graphics
{
    class Texture;
    class Mesh;
}

using namespace Dusk::Graphics;

namespace World
{

class Skybox :
    public Arc::ManagedObject
{
public:

    inline Skybox( void ) :
        mp_Mesh(nullptr),
        mp_Texture(nullptr)
    { }

    virtual ~Skybox( void );

    virtual inline string getClassName( void ) const { return "Skybox "; }

    bool load( const string& filename );
    void render( void );

private:

    Mesh*       mp_Mesh;
    Texture*    mp_Texture;

}; // class Skybox

} // namespace World

} // namespace Dusk

#endif // DUSK_SKYBOX_H
