#ifndef DUSK_IMPORT_TGA_H
#define DUSK_IMPORT_TGA_H

#include <string>

#include "InterTexture.h"

using std::string;

bool ImportTGA(const string& filename, InterTexture* pTexture);

#endif // DUSK_IMPORT_TGA_H