#include "ExportDSKT.h"

#include <Export/ExportPNG.h>

bool ExportDSKT(const string& filename, InterTexture* pTexture)
{
    return ExportPNG(filename, pTexture);
}
