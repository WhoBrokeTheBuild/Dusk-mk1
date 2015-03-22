#include "ImportPNG.h"

#include <Util/Functions.h>

bool ImportPNG( const string& filename, InterTexture* pTexture )
{
    return import_image(filename, pTexture);
}
