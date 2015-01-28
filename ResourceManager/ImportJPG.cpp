#include "ImportJPG.h"

#include "Functions.h"

bool ImportJPG(const string& filename, InterTexture* pTexture)
{
	return import_image(filename, pTexture);
}
