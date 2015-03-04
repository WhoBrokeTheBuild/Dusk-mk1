#ifndef DUSK_EXPORT_TGA_H
#define DUSK_EXPORT_TGA_H

#include <string>

#include <Intermediate/InterTexture.h>

using std::string;

bool ExportTGA(const string& filename, InterTexture* pTexture);

#endif // DUSK_EXPORT_TGA_H
