#ifndef DUSK_INTER_TEXTURE_H
#define DUSK_INTER_TEXTURE_H

#include <Arc/ManagedObject.h>
#include <Arc/ArrayList.h>

using Arc::ArrayList;

class InterTexture :
	public Arc::ManagedObject
{
public:

	virtual inline string getClassName(void) const { return "Intermediate Texture"; }

    unsigned int                Width,
                                Height;

    ArrayList<unsigned char>    Pixels;
};

#endif // DUSK_INTER_TEXTURE_H
