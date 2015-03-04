#ifndef DUSK_MESH_H
#define DUSK_MESH_H

#include <Arc/ManagedObject.h>
#include <Graphics/Graphics.h>
#include <Graphics/Material.h>
#include <Math/Math.h>

#include <Arc/ArrayList.h>

using Arc::ArrayList;

namespace Dusk
{

namespace Graphics
{

class Mesh :
    public Arc::ManagedObject
{
public:

    static const GLAttribute ATTR_VERTEX;
    static const GLAttribute ATTR_NORMAL;
    static const GLAttribute ATTR_TEX_COORD;

    inline Mesh( void ) :
        m_Name(),
        m_VertexBuffer(0),
        m_NormalBuffer(0),
        m_TexCoordBuffer(0),
        m_VertexArray(0),
        mp_Material(nullptr)
    { }

    virtual inline string getClassName( void ) const { return "Mesh"; }

    bool init( const string& name, const GLPrimitiveType& primitiveType, const ArrayList<vec3>& vertexes, const ArrayList<vec3>& normals = ArrayList<vec3>(), const ArrayList<vec2>& texCoords = ArrayList<vec2>() );
    bool init( const string& name, const GLPrimitiveType& primitiveType, const unsigned int& vertexCount, const vec3* pVertexes, const vec3* pNormals = nullptr, const vec2* pTexCoords = nullptr );
    bool init( const string& name, const GLPrimitiveType& primitiveType, const unsigned int& vertexCount, const float* pVertexes, const float* pNormals = nullptr, const float* pTexCoords = nullptr );
    virtual inline ~Mesh( void ) { term(); }

    void render( void );

    bool hasMaterial( void ) const { return (mp_Material); }
    Material* getMaterial( void ) { return mp_Material; }
    void setMaterial( Material* pMaterial ) { mp_Material = pMaterial; }

private:

    Mesh( const Mesh& rhs );
    void operator=( const Mesh& rhs );

    void term( void );

    string          m_Name;

    unsigned int    m_VertexCount;

    GLPrimitiveType m_PrimitiveType;

    GLBuffer        m_VertexBuffer,
                    m_NormalBuffer,
                    m_TexCoordBuffer;

    GLVertexArray   m_VertexArray;

    Material*       mp_Material;

}; // class Mesh

} // namespace Graphics

} // namespace Dusk

#endif // DUSK_MESH_H
