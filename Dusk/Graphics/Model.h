#ifndef DUSK_MODEL_H
#define DUSK_MODEL_H

#include <Arc/ManagedObject.h>

#include <Arc/ArrayList.h>

using Arc::ArrayList;

namespace Dusk
{

namespace Graphics
{

class Mesh;

class Model :
    public Arc::ManagedObject
{
public:

    inline Model( void ) :
        m_Meshes()
    { }
    ~Model( void );

    virtual inline string getClassName( void ) const { return "Model"; }

    bool load( const string& filename );
    void render( void );
    ArrayList<Mesh*> getMeshList( void );

private:

    ArrayList<Mesh*>    m_Meshes;

};

} // namespace Graphics

} // namespace Dusk

#endif // DUSK_MODEL_H
