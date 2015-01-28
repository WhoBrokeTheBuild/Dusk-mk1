#include "ImportPNG.h"

#include "Functions.h"

bool ImportPNG( const string& filename, InterTexture* pTexture )
{
    return import_image(filename, pTexture);
}
