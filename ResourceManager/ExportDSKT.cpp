#include "ExportDSKT.h"

#include "ExportPNG.h"

bool ExportDSKT(const string& filename, InterTexture* pTexture)
{
    return ExportPNG(filename, pTexture);
}
