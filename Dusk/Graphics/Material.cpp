#include "Material.h"

bool Dusk::Graphics::Material::init( const string& name,
                                     const string& diffuseMap, const string& ambientMap, const string& specularMap,
                                     const string& specularHilightMap, const string& alphaMap, const string& bumpMap,
                                     const float& specular, const float& transparency,
                                     const vec3& ambientColor, const vec3& diffuseColor, const vec3& specularColor )
{
    m_Name = name;
    m_DiffuseMap = diffuseMap;
    m_AmbientMap = ambientMap;
    m_SpecularMap = specularMap;
    m_SpecularHilightMap = specularHilightMap;
    m_AlphaMap = alphaMap;
    m_BumpMap = bumpMap;
    m_Specular = specular;
    m_Transparency = transparency;
    m_AmbientColor = ambientColor;
    m_DiffuseColor = diffuseColor;
    m_SpecularColor = specularColor;

    return true;
}
