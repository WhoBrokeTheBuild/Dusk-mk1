#include "Material.h"

#include <Graphics/Texture.h>
#include <Logging/Log.h>

using namespace Dusk::Logging;

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

    mp_DiffuseMapTexture = nullptr;

    LogInfoFmt(getClassName(), "Attempting to load diffuse texture \"%s\"", m_DiffuseMap.c_str());
    if (!m_DiffuseMap.empty())
    {
        mp_DiffuseMapTexture = New Texture();
        if ( ! mp_DiffuseMapTexture->load(m_DiffuseMap))
        {
            LogErrorFmt(getClassName(), "Failed to load texture \"%s\"", m_DiffuseMap.c_str());
            return false;
        }
    }

    return true;
}

void Dusk::Graphics::Material::term( void )
{
    delete mp_DiffuseMapTexture;
    mp_DiffuseMapTexture = nullptr;
}

void Dusk::Graphics::Material::bind( void )
{
    if (mp_DiffuseMapTexture)
    {
    	glActiveTexture(GL_TEXTURE0);
        mp_DiffuseMapTexture->bind();
    }
}
