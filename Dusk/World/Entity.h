#ifndef DUSK_ENTITY_H
#define DUSK_ENTITY_H

#include <Arc/ManagedObject.h>

#include <Math/Math.h>
#include <Arc/ArrayList.h>

using Arc::ArrayList;

namespace Dusk
{

namespace Graphics
{
    class Model;
}

using namespace Dusk::Graphics;

namespace World
{

class Entity :
    public Arc::ManagedObject
{
public:

    Entity( void );
    virtual ~Entity( void );

    virtual inline string getClassName( void ) const { return "Entity"; }

    bool init( void );
    void render( void );

    bool addModel( Model* pModel );

    vec3 getPos( void ) const { return m_Pos; }
    vec3 getRot( void ) const { return m_Rot; }
    vec3 getScale( void ) const { return m_Scale; }

    void setPos( vec3 pos ) { m_Pos = pos; }
    void setRot( vec3 rot ) { m_Rot = rot; }
    void setScale( vec3 scale ) { m_Scale = scale; }

private:

    vec3    m_Pos,
            m_Rot,
            m_Scale;

    ArrayList<Model*>   m_Models;

};

} // namespace World

} // namespace Dusk

#endif // DUSK_ENTITY_H
