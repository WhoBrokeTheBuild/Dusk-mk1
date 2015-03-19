#include "ImportDSKT.h"

#include <Import/ImportPNG.h>

bool ImportDSKT(const string& filename, InterTexture* pTexture)
{
    return ImportPNG(filename, pTexture);
}
