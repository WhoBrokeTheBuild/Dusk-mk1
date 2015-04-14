#include "ImportTGA.h"

#include <Util/Functions.h>

bool ImportTGA(const string& filename, InterTexture* pTexture)
{
    return import_image(filename, pTexture);
}
