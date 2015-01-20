#ifndef DUSK_INTER_TEXTURE_H
#define DUSK_INTER_TEXTURE_H

#include <Arc/ManagedObject.h>

class InterTexture :
	public Arc::ManagedObject
{
public:

	virtual inline string getClassName(void) const { return "Intermediate Texture"; }
};

#endif // DUSK_INTER_TEXTURE_H
