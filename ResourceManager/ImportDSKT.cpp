#include "ImportDSKT.h"

#include "ImportPNG.h"

bool ImportDSKT(const string& filename, InterTexture* pTexture)
{
    return ImportPNG(filename, pTexture);
}
