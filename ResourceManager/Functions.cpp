#include "Functions.h"

#include <Arc/StringFunctions.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void error( const string& msg, const bool& fatal /*= true*/ )
{
	printf("Error: %s\n", msg.c_str());
    if (fatal)
        exit(1);
}

string parse_ext( const string& str )
{
    size_t period_pos = str.rfind('.');

    if (period_pos == string::npos)
        return "";

    string ext = str.substr(period_pos + 1);

    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

    return ext;
}

void copy_pixels( unsigned char* source, unsigned char* dest, const unsigned int& x, const unsigned int& y,
                  const unsigned int& pitch, const unsigned short& bytesPerPixel, const bool& reverse )
{
    unsigned int sourceOffset = ( (y * pitch) + x ) * bytesPerPixel;
    unsigned int destOffset = ( (y * pitch) + x ) * 4;

    for (unsigned int i = 0; i < 3; ++i)
    {
        if (reverse)
        {
            dest[destOffset + i] = source[sourceOffset + ( 2 - i)];
        }
        else
        {
            dest[destOffset + i] = source[sourceOffset + i];
        }
    }

    if (bytesPerPixel == 4)
    {
        dest[destOffset + 3] = source[sourceOffset + 3];
    }
    else
    {
        dest[destOffset + 3] = 255;
    }
}

bool import_image( const string& filename, InterTexture* pTexture )
{
    string ext = Arc::Arc_FileExtension(filename);

    SDL_Surface* pSurface = IMG_Load(filename.c_str());

    bool reverseBytes = false;
    if (ext == "tga")
        reverseBytes = true;

    unsigned short bytesPerPixel = pSurface->format->BytesPerPixel;

    unsigned int width, height;

    width = pSurface->w;
    height = pSurface->h;

    pTexture->Width = width;
    pTexture->Height = height;
    pTexture->Pixels.resize(width * height * 4);
    unsigned char* pDest = &pTexture->Pixels[0];

    for (unsigned int y = 0; y < height; ++y)
    {
        for (unsigned int x = 0; x < width; ++x)
        {
            copy_pixels((unsigned char*)pSurface->pixels, pDest, x, y, pSurface->pitch, bytesPerPixel, reverseBytes);
        }
    }

    SDL_FreeSurface(pSurface);

    return true;
}
