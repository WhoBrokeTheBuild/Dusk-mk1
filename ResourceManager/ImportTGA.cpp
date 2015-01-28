#include "ImportTGA.h"

#include "Functions.h"

bool ImportTGA(const string& filename, InterTexture* pTexture)
{
    return import_image(filename, pTexture);
}
