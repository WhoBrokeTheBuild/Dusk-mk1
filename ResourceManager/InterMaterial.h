#ifndef DUSK_INTER_MATERIAL_H
#define DUSK_INTER_MATERIAL_H

#include <Arc/ManagedObject.h>

#include "Math.h"

class InterMaterial :
	public Arc::ManagedObject
{
public:

	virtual inline string getClassName(void) const { return "Intermediate Material"; }

	string Name;
	float Specular;
	vec3 AmbientColor;
	vec3 DiffuseColor;
	vec3 SpecularColor;
	float transparency;
	
};

#endif // DUSK_INTER_MATERIAL_H