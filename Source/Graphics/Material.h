#ifndef MATERIAL_H
#define MATERIAL_H

#include <Arc/ManagedObject.h>
#include <Math/Math.h>

namespace Dusk
{

namespace Graphics
{

class Material :
    public Arc::ManagedObject
{
public:

    bool init( const string& name,
               const string& diffuseMap, const string& ambientMap, const string& specularMap,
               const string& specularHilightMap, const string& alphaMap, const string& bumpMap,
               const float& specular, const float& transparency,
               const vec3& ambientColor, const vec3& diffuseColor, const vec3& specularColor );

    virtual inline string getClassName( void ) const { return "Material"; }

    inline string getName( void ) const { return m_Name; }

    inline string getDiffuseMapPath        ( void ) const { return m_DiffuseMap; }
    inline string getAmbientMapPath        ( void ) const { return m_AmbientMap; }
    inline string getSpecularMapPath       ( void ) const { return m_SpecularMap; }
    inline string getSpecularHilightMapPath( void ) const { return m_SpecularHilightMap; }
    inline string getAlphaMapPath          ( void ) const { return m_AlphaMap; }
    inline string getBumpMapPath           ( void ) const { return m_BumpMap; }

    inline float getSpecular( void ) const { return m_Specular; }
    inline float getTransparency( void ) const { return m_Transparency; }

    inline vec3 getAmbientColor ( void ) const { return m_AmbientColor; }
    inline vec3 getDiffuseColor ( void ) const { return m_DiffuseColor; }
    inline vec3 getSpecularColor( void ) const { return m_SpecularColor; }

private:

    string  m_Name;

    string  m_DiffuseMap,
            m_AmbientMap,
            m_SpecularMap,
            m_SpecularHilightMap,
            m_AlphaMap,
            m_BumpMap;

    float   m_Specular,
            m_Transparency;

    vec3    m_AmbientColor,
            m_DiffuseColor,
            m_SpecularColor;
};

} // Graphics

} // Dusk

#endif // MATERIAL_H
