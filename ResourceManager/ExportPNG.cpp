#include "ExportPNG.h"

#include "savepng.h"

bool ExportPNG(const string& filename, InterTexture* pTexture)
{
    if (pTexture->Width == 0 || pTexture->Height == 0)
        return false;

    Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    SDL_Surface* pSurface = SDL_CreateRGBSurfaceFrom(&pTexture->Pixels[0], pTexture->Width, pTexture->Height, 32, pTexture->Width * 4, rmask, gmask, bmask, amask);

    if (pSurface == nullptr)
        return false;

    SDL_SavePNG(pSurface, filename.c_str());

    SDL_FreeSurface(pSurface);

	return true;
}
