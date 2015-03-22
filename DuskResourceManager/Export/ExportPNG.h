#ifndef DUSK_EXPORT_PNG_H
#define DUSK_EXPORT_PNG_H

#include <string>

#include <Intermediate/InterTexture.h>

using std::string;

bool ExportPNG(const string& filename, InterTexture* pTexture);

#endif // DUSK_EXPORT_PNG_H
