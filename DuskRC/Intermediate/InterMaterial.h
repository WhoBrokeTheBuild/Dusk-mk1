#ifndef DUSK_INTER_MATERIAL_H
#define DUSK_INTER_MATERIAL_H

#include <Arc/ManagedObject.h>

#include <Util/Math.h>

class InterMaterial :
	public Arc::ManagedObject
{
public:

	virtual inline string getClassName(void) const { return "Intermediate Material"; }

	string  Name;

    string  DiffuseMap,
            AmbientMap,
            SpecularMap,
            SpecularHilightMap,
            AlphaMap,
            BumpMap;

	float   Specular,
            Transparency;

	vec3    AmbientColor,
            DiffuseColor,
            SpecularColor;

};

#endif // DUSK_INTER_MATERIAL_H
