#include "ImportJPG.h"

#include <Util/Functions.h>

bool ImportJPG(const string& filename, InterTexture* pTexture)
{
	return import_image(filename, pTexture);
}
